import collections
# might need to install pycryptodomex into sage:
# sage -sh
# pip3 install pycryptodomex
# exit
from Cryptodome.Hash import SHAKE256

if len(sys.argv) != 3:
    print("Usage: <script> <n> <num_rounds>")
    exit()

n = int(sys.argv[1])
num_rounds = int(sys.argv[2])
if n not in [64, 128, 192, 256]:
    print("Only n \in \{64, 128, 192, 256\} supported.")
    exit()

F = None
if n == 64:
    F.<z> = GF(2^n)
elif n == 128:
    F.<z> = GF(2^n, modulus=x^128 + x^7 + x^2 + x + 1)
elif n == 192:
    F.<z> = GF(2^n, modulus=x^192 + x^7 + x^2 + x + 1)
elif n == 256:
    F.<z> = GF(2^n, modulus=x^256 + x^10 + x^5 + x^2 + 1)


def gen_random_numbers(state_size,num_rounds):
    shake = SHAKE256.new()
    shake.update('Rain-{}-{}'.format(state_size, num_rounds).encode('utf-8'))
    while True:
        bytes = shake.read(int(state_size/8))
        yield int.from_bytes(bytes, byteorder='big')

rand_gen = gen_random_numbers(n, num_rounds)

def rotate_list_right(l, n):
    d = collections.deque(l)
    d.rotate(n)
    return d

def build_lin_perm_poly(n):
    poly_coefficients = [F.fetch_int(next(rand_gen)) for i in range(0, n)]
    matrix_dickson = matrix(F, [rotate_list_right([poly_coefficients[j]^(2^i) for j in range(0, n)], i) for i in range(0, n)])
    while F.fetch_int(0) in poly_coefficients or matrix_dickson.is_invertible() == False:
        poly_coefficients = [F.fetch_int(next(rand_gen)) for i in range(0, n)]
        matrix_dickson = matrix(F, [rotate_list_right([poly_coefficients[j]^(2^i) for j in range(0, n)], i) for i in range(0, n)])
    return poly_coefficients

def build_inverse_poly(poly_coefficients):
    matrix_dickson = matrix(F, [rotate_list_right([poly_coefficients[j]^(2^i) for j in range(0, n)], i) for i in range(0, n)])
    determinant = matrix_dickson.determinant()
    adjugate = matrix_dickson.adjugate()
    poly_inverse_coefficients = [(1/determinant) * (adjugate[0, i]) for i in range(0, n)]
    return poly_inverse_coefficients

def build_mat_from_poly(poly_coefficients):
    M = matrix(GF(2), n, n)

    # Precompute basis and polynomial evaluations
    basis = [F.fetch_int(2)^(i) for i in range(0, n)]
    dual_basis = F.dual_basis()
    poly_evaluations = [sum([poly_coefficients[j] * (basis[i]^(2^j)) for j in range(0, n)]) for i in range(0, n)]

    # Construct matrix
    for i in range(0, n):
        for j in range(0, n):
            M[i,j] = (dual_basis[i] * poly_evaluations[j]).trace()

    return M

def print_mat(M):
    for i in range(0,n):
        for vals in range(0, n//64):
            val = 0
            for j in range(0,64):
                bit = M[i,vals*64 + j]
                val |= int(bit) << int(j)
            print(hex(val), end=",")
        print()


def build_linear_layer(n):
    poly_coefficients = build_lin_perm_poly(n)
    poly_inverse_coefficients = build_inverse_poly(poly_coefficients)
    while F.fetch_int(0) in poly_inverse_coefficients:
        poly_coefficients = build_lin_perm_poly(n)
        poly_inverse_coefficients = build_inverse_poly(poly_coefficients)
    M = build_mat_from_poly(poly_coefficients)
    print("matrix:")
    print_mat(M)
    print("="*80)
    print("matrix.transposed:")
    print_mat(M.transpose())
    print("="*80)
    return (M, poly_coefficients)


def permutation(plaintext, key, round_constants, lin_mats, num_rounds):
    state = plaintext

    # First r-1 rounds
    for i in range(0, num_rounds - 1):
        # Key and constant addition
        state = state + key + round_constants[i]
        if state != 0:
            state = state^(-1)
        state = F.fetch_int(ZZ(list(lin_mats[i][0] * vector(state)), base=2))
        #state = sum([lin_mats[i][1][j] * (state^(2^j)) for j in range(0, n)])
    
    # Last round
    state = state + key + round_constants[num_rounds - 1]
    if state != 0:
        state = state^(-1)
    state = state + key

    return state

print("--- n = " + str(n) + " ---")
print("Irreducible polynomial:", F.modulus())
print("----------")

# Generate round constants
print("--- ROUND CONSTANTS ---")
round_constants = []
for i in range(0, num_rounds):
    print("Round " + str(i) + ":")
    rc = next(rand_gen)
    round_constants.append(F.fetch_int(rc))
    print(hex(rc))

# Generate linear layers
print("--- LINEAR LAYERS ---")
linear_layers = []
for i in range(0, num_rounds - 1):
    print("Round " + str(i) + ":")
    (mat, poly_coefficients) = build_linear_layer(n)
    linear_layers.append((mat,poly_coefficients))
    inverse_poly_coefficients = build_inverse_poly(poly_coefficients)
    mat_inverse = build_mat_from_poly(inverse_poly_coefficients)
    print("Matrix:\n" + str(mat))
    print("Linearized polynomial coefficients:\n" + str([hex(coeff.integer_representation()) for coeff in poly_coefficients]))
    print("----------")
    print("Invertible:", mat.is_invertible())
    print("mat_inverse == mat.inverse():", mat_inverse == mat.inverse())
    print("len(poly_coefficients):", str(len(poly_coefficients)))
    print("len(inverse_poly_coefficients):", str(len(inverse_poly_coefficients)))
    print("No 0 in poly_coefficients:", str(F.fetch_int(0) not in poly_coefficients))
    print("No 0 in inverse_poly_coefficients:", str(F.fetch_int(0) not in inverse_poly_coefficients))

# compute some testvectors:
print("\n\n===TESTVECTORS===")
for i in range(5):
    plaintext = F.fetch_int(next(rand_gen))
    key = F.fetch_int(next(rand_gen))
    ciphertext = permutation(plaintext, key, round_constants, linear_layers, num_rounds)
    print("K:", hex(key.integer_representation()))
    print("P:", hex(plaintext.integer_representation()))
    print("C:", hex(ciphertext.integer_representation()))
    print("-"*80)

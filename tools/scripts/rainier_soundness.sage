
def sigSize(kappa, n, r, N, tau):
    sigSize = 0.0
    sigSize += 256  # salt
    sigSize += 4*kappa  # h_1, h_2
    proofSize = 0.0
    proofSize += r * n  # T_i
    proofSize += (r+1) * n  # P(r+1..2r+1)
    proofSize += 2*(n)  # S(R), T(R)
    proofSize += kappa * ceil(log(N, 2))  # reveallist of merkle tree
    proofSize += 2*kappa  # C_e for missing party
    proofSize += n  # keyshare for missing party
    sigSize += tau * proofSize
    return sigSize/8

def PMF(n, k, p):
    return sum(binomial(n, kk) * p**kk * (1-p)**(n-kk) for kk in range(k, n+1))


def soundness(fieldsize, N, tau, L):
    min_cost = Infinity
    min_tau = -1
    for tau1 in range(0, tau+1):
        cost = 1.0/PMF(tau, tau1, (2.0*L/(2**fieldsize - L))) + \
            N ^ (tau-tau1)
        if cost < min_cost:
            min_cost = cost
            min_tau = tau1

    return (min_cost, min_tau)

def print_helper(kappa, n, N, tau, L, cost):
    print("N={}, tau={}: 2^{:.3f} attack cost, SigSize: {:.2f}".format(
            N, tau, float(log(cost, 2)), float(sigSize(kappa, n, L, N, tau))))

def printSoundness(kappa, n, L, players_repetitions):
    print("{}-bit security, F_2^{}, {} rounds".format(kappa, n, L))
    for N, tau in players_repetitions:
        print_helper(kappa, n, N, tau, L, soundness(n, N, tau, L)[0])


# gets the minimum number of repetitions tau for the given number of players
def findSoundness(kappa, n, L, players):
    print("{}-bit security, F_2^{}, {} rounds".format(kappa, n, L))
    for N in players:
        for tau in range(2*kappa):
            cost, tau_1 = soundness(n, N, tau, L)
            if cost > 2**kappa:
                print_helper(kappa, n, N, tau, L, cost)
                break


# gets the minimum number of players for the given rounds
def findSoundness2(kappa, n, L, rounds):
    print("{}-bit security, F_2^{}, {} rounds".format(kappa, n, L))
    for tau in rounds:
        for N in range(0, 2**16):
            cost, tau_1 = soundness(n, N, tau, L)
            if cost > 2**kappa:
                print_helper(kappa, n, N, tau, L, cost)
                break


print("-"*80)
players = list(range(3,17))
# 128 bit
findSoundness(128, 128, 3, [int(2**n) for n in players])
#findSoundness(128, 128, 4, [int(2**n) for n in players])

print("-"*80)
# 192 bit
findSoundness(192, 192, 3, [int(2**n) for n in players])

print("-"*80)
## 256 bit
findSoundness(256, 256, 3, [int(2**n) for n in players])
# Rainier Signatures 

This repository contains the code for the Rainier signature scheme from our paper

**Shorter Signatures Based on Tailor-Made Minimalist Symmetric-Key Crypto**  
*Christoph Dobraunig and Daniel Kales and Christian Rechberger and Markus Schofnegger and Greg Zaverucha*

The implementation of the additionally proposed variants of Banquet can be found [here](https://github.com/IAIK/banquet-signature-variants).


## Requirements

C++-17 Compatible Toolchain

For testing:

* [GMP](https://gmplib.org/)
* [NTL](https://shoup.net/ntl)

## Setup

```bash
mkdir build
cd build
cmake ..
make 
# tests (only if you built them)
make test
# benchmarks
./bench_free -i <iterations> <kappa> <N> <tau> #benchmark parameters freely
python3 ../tools/bench_all.py # benchmarks some of the selected parameters
```

The benchmark script contains a `SCALING_FACTOR` variable that is used to scale the measured cycles to ms. Configure it according to your specific machine.


## Additional Scripts

Some additional scripts to generate new Rain instances or to calculate the soundness and signature size of a given parameter set can be found in the `tools/scripts` folder.
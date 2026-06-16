# Divide

## Problem Description

Given a number \( n \), determine the number of values of \( x \) that satisfy the following equation:  

\[
\varphi(x) \mid n
\]

where \( \mid \) denotes divisibility, meaning \( a \mid b \) indicates that \( a \) divides \( b \).  

\( \varphi(x) \) represents Euler's totient function. See the problem background for more details.  


## Input Format

_Mirja has already implemented the Pollard-Rho algorithm for you,_  
so the input provides \( n \) in its **prime factorized form** as follows:  

\[
n = \prod_{i=1}^{s} p_i^{\alpha_i}
\]

For each test case, we first provide an integer \( s \), followed by \( s \) lines. Each line contains two integers, \( p_i \) and \( \alpha_i \), representing the prime factor and its exponent, respectively.  
It is guaranteed that \( p_i < p_{i+1} \).  

## Output Format

The output should be taken modulo **998244353**.  

## Sample Input #1

```text
1
2 3
```

## Sample Output #1

```text
14
```

## Sample Input #2

```text
3
2 3
11 1
23 1
```

## Sample Output #2

```text
53
```

## Sample Input #3

```text
6
2 1
3 2
5 1
7 1
101 2
178187 1
```

## Sample Output #3

```text
53
```

## Explanation

The given prime factorizations correspond to:
	•	Sample 1: ( n = 8 )
	•	Sample 2: ( n = 2024 )
	•	Sample 3: ( n = 1145141919810 )

For Sample 1, the 14 valid values of ( x ) are: 
$\varphi(15)=\varphi(16)=\varphi(20)=\varphi(24)=\varphi(30)=8\mid 8$  
$\varphi(5)=\varphi(8)=\varphi(10)=\varphi(12)=4\mid 8$  
$\varphi(3)=\varphi(4)=\varphi(6)=2\mid 8$  
$\varphi(1)=\varphi(2)=1\mid 8$

## Constraints

For 100% of test cases
- $n \in [1, 10^{18}]$
- $s \geq 1$
- $p$ is guaranteed to be a prime number.

# 互质与整除

# 思路分析

## 先表示出答案函数 $a(n)$ 

定义 [$\psi(n)$](https://oeis.org/A014197)：方程 $\varphi(x)=n$ 的 $x$ 的解数。  
答案 [$a(n)$](https://oeis.org/A070633) 即为 $\sum_{d\mid n}\psi(d)$。

定义 $\psi(n)$ 的 Dirichlet 生成函数：
$$\tilde{\Psi}(x)=\sum_{n\ge1}\frac{\psi(n)}{n^x}$$


由于每有一个 $\varphi(x)=n$ 就对 $\psi(n)$ 产生 $1$ 的贡献，  
由此我们可以化简 $\tilde{\Psi}(x)$：

$$
\begin{aligned}
\tilde{\Psi}(x)&=\sum_{n\ge1}\frac{\psi(n)}{n^x}=\sum_{n\ge1}\frac{1}{\varphi^x(n)}\\
&=\prod_{p\in\mathcal{P}}\left(1+\sum_{i\ge1}\frac{1}{\varphi^x(p^i)}\right)\\
&=\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}+(p^2-p)^{-x}+(p^3-p^2)^{-x}+\dots)\\
&=\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}(1+p^{-x}+p^{-2x}+\dots))\\
&=\prod_{p\in\mathcal{P}}\left(1+\frac{(p-1)^{-x}}{1-p^{-x}}\right)\\
&=\zeta(x)\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}-p^{-x})\\
\end{aligned}
$$

后面的乘积难以化简，于是我们将其单独提出。
即为定义 $f(n)$ 的 Dirichlet 生成函数：

$$\tilde{F}(x)=\sum_{n\ge1}\frac{f(n)}{n^x}=\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}-p^{-x})$$

那么答案函数 $a(n)$ 的 Dirichlet 生成函数为：
$$\tilde{\Alpha}(x)=\zeta(x)\tilde{\Psi}(x)=\zeta^2(x)\tilde{F}(x)$$

又因为 $\zeta^2(x)$ 是 $\sigma_0(n)$ 的 Dirichlet 生成函数，  
所以答案函数：
$$a(n)=\sum_{d\mid n}f(d)\sigma_0\left(\frac{n}{d}\right)$$

## 现在考虑快速计算 $f(d)$ 

如果直接将其看做背包问题 dp，  
那么时间复杂度为 $O(\sigma_0^2(n))$。

$$f(d)=[d^{-x}]\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}-p^{-x})$$

一种很自然的想法是对其用多项式加速 dp，但这并不是多项式。

我们模仿贝尔级数的思想，定义 $x_i=p_i^{-x}$，其中 $p_i$ 为第 $i$ 小的质数。  
对任意一项因式分解就可以将其转为单项式：

$$n^{-x}=\left(\prod_{i\ge1} p_i^{t_{i,n}}\right)^{-x}=\prod_{i\ge1} x_i^{t_{i,n}}$$

于是可以把 Dirichlet 生成函数转成多元普通生成函数：

$$f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\prod_{p\in\mathcal{P}}\left(1+\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)$$

仿照 [P4389 付公主的背包](https://www.luogu.com.cn/problem/P4389) 优化 0/1 背包：
$$f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{p\in\mathcal{P}}\ln\left(1+\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)\right)$$

对其展开成形式幂级数：
$$
\begin{aligned}
f(d)&=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{p\in\mathcal{P}}\sum_{k\ge1}\frac{(-1)^{k+1}}{k} \left(\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)^k\right)\\
&=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{p\in\mathcal{P}}\sum_{\substack{j,k\ge0\\[3pt]j+k\ne0}}\frac{(-1)^{j+1}}{j+k}\binom{j+k}{j}\left(\prod_{i\ge1} x_i^{t_{i,p-1}}\right)^j\left(\prod_{i\ge1} x_i^{t_{i,p}}\right)^k\right)
\end{aligned}
$$

但是这样会有一个小问题：  
当 $p=2$ 时要计算 $ln(2-x_1)$  
但是很可惜，不能按上方一般的形式展开，所以我们可以将其单独提出：
$$
f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{\substack{p\in\mathcal{P}\\[3pt]p\ne2}}\sum_{\substack{j,k\ge0\\[3pt]j+k\ne0}}\frac{(-1)^{j+1}}{j+k}\binom{j+k}{j}\left(\prod_{i\ge1} x_i^{t_{i,p-1}}\right)^j\left(\prod_{i\ge1} x_i^{t_{i,p}}\right)^k\right)(2-x_1)
$$

由于对于所有的 $d\mid n$，都有 $t_{i,d}<t_{i,n}$  
且已经给出了 $n$ 的标准质因子分解形式 $n=\prod_{i=1}^s p_i^{\alpha_i}$。  

所以我们仅需计算 $s$ 维，每一维都分别的次数都分别低于 $\alpha_i$ 的多项式的 exp。

# 多元多项式

接下来最后一步就是多元多项式 exp 了，  
我这里主要是复读 [> EI 大神的 blog <](https://www.luogu.com/article/wje8kchr) 和有关 Uoj#596 的 blog，  
在此之前我们先浅谈一下多元多项式。

这里约定多元多项式为 $s$ 维，每一维都分别的次数都分别 $\le\alpha_i$ 的多项式。  
那么它的值域 $N=\prod_{i=1}^s(\alpha_i+1)=\sigma_0(n)$

## 多元多项式 DFT/IDFT

多元多项式 DFT 相当于按顺序依次对其每一维 DFT。  
多元多项式 IDFT 相当于反向按顺序的依次对其每一维 IDFT。

那么为什么多元多项式 DFT 就是依次对其每一维 DFT 呢？  
因为做 DFT 相当于把系数表示法转为了点值表示法，  
所以依次对其每一维带入单位根即可计算点值。

由于多元多项式 DFT 是线性算法。  
有「求逆原理」：$(A_1A_2\dots A_s)^{-1}=A_s^{-1}A_{s-1}^{-1}\dots A_1^{-1}$  
这样就得到了多元函数的 IDFT 算法。

## 多元多项式乘法

我们计算卷积 $F(x_1,x_2,\dots,x_s)\cdot G(x_1,x_2,\dots,x_s)$，  
可以发现卷积后的值域为 $\prod_{i=1}^s(2\alpha_i+1)=O(2^sN)$

然而实际上大多数情况下我们仅需计算 $\bmod(x_1^{\alpha_1},x_2^{\alpha_2},\dots,x_s^{\alpha_s})$ 意义下的值。  
若 $s$ 较大，值域将会急剧膨胀，这被称为维度爆炸。  
而 EI 以一种构造性的算法解决了这个问题：

显然，高维多项式是要避免的。  
于是我们将下标 $\vec{i}=(i_1,i_2,\dots,i_s)$ 编码为一个 $(\alpha_1+1,\alpha_2+1,...,\alpha_s+1)$ 进制数。  
即令 $\lvert\vec{i}\rvert=\sum\limits_{t=1}^si_t\prod_{n=1}^{t-1}(\alpha_n-1)=i_1+i_2*(\alpha_1+1)+...+i_s*(\alpha_1+1)*(\alpha_2+1)*...*(\alpha_{s-1}+1)$。  
这样就把多维映射到了一维上，下标 $\vec{i}$ 和编码 $\lvert\vec{i}\rvert$ 是一一对应的。  
而且可以发现大多数时候有 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$。    
所以多元多项式可以被这样的一元多项式来代替：
$$F(x_1,x_2,\dots,x_s)=\sum_{\substack{\vec{i}=(i_1,\dots,i_s)\\i_1\le \alpha_1,\dots,i_s\le \alpha_s}}^{}f_{\vec{i}}x_1^{i_1}\dots x_s^{i_s}\textcolor{red}\to F(x)=\sum_{i=0}^{N-1}f_ix^i$$

其中 $f_{\vec{i}}=f_{\lvert\vec{i}\rvert}$。

只有 $\vec{i}+\vec{j}$ 超过了模意义的范围时 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$ 才不成立，  
所以我们要将超出范围（产生进位）的贡献去除（我们要计算模意义下的卷积）。  
考虑占位函数 $\chi(n)$，使得 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$ 成立当且仅当 $\chi(i)+\chi(j)=\chi(i+j)$。  
这样，我们计算二元幂级数 $\sum_i f_ix^iy^{\chi(i)}$ 的卷积，然后利用第二维去除无用贡献即可。

接下来就是 EI 的一个精妙构造了：

由于 $[i_t+j_t\le \alpha_t]=\left\lfloor\frac{i+j}{\prod_{n=1}^{t-1}(\alpha_n+1)}\right\rfloor-\left\lfloor\frac{i}{\prod_{n=1}^{t-1}(\alpha_n+1)}\right\rfloor-\left\lfloor\frac{j}{\prod_{n=1}^{t-1}(\alpha_n+1)}\right\rfloor\in\{0,1\}$

令 $\chi(i)=\sum\limits_{t=1}^{s-1}\left\lfloor \frac{i}{\prod_{n=1}^{t}(\alpha_n+1)}\right\rfloor=\left\lfloor \frac{i}{(\alpha_1+1)}\right\rfloor+...+\left\lfloor \frac{i}{(\alpha_1+1)(\alpha_2+1)...(\alpha_{s-1}+1)}\right\rfloor$

这个占位函数是极好的，因为 $\chi(i+j)-\chi(i)-\chi(j)\in[0,s)$。  
所以 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$ 成立当且仅当 $\chi(i)+\chi(j)\equiv\chi(i+j)\pmod{s}$。  

我们令 $1\equiv y^s$，相当于模 $y^s-1$ 的循环卷积。  
这样，值域也被这么压缩到了 $sN$。

## 多元多项式全家桶

多元多项式的其他运算可以直接套一元多项式的模板。

对其求导可以考虑一个特殊的微分算子 $\mathfrak{D}=x\frac{d}{dx}$，  
这里的 $x$ 是压缩成一维时的变量。  

可以发现它满足常见的导数性质，  
这样就解决了多项式 ln 和牛顿迭代。

# 算法工程

时间复杂度分为：  
1. 判 $\sigma_0(n)$ 次质数（所有的 $d+1$）：$O(\sigma_0(n)\log n)$
2. 计算 exp 之前的级数：$O(\sigma_0(n))$
3. 多元多项式 exp：$\Theta(s\sigma_0(n)\log\sigma_0(n))$

第 $2$ 处的时间复杂度证明（不严谨）：  
若所有质因子减 $1$ 都还是因子：$O(s\log^2(n))$  
若所有因子加 $1$ 都是质数（除去上方情况）：$A309891(n)+\sigma_0(n)$  
当 $\sigma_0(n)$ 较大时这里的时间复杂度就为 $O(\sigma_0(n))$  
~~较小时就没必要考虑时间复杂度了~~  

第 $3$ 处的时间复杂度以及实现方法，对于卷积部分：  
做 $s$ 个长为 $2N$ 的 DFT，  
然后在 $y$ 维暴力进行卷积，相当于进行了 DFT+IDFT。  
再做 $s$ 个长为 $2N$ 的 IDFT，  
卷积顺序正确性可以看上方的证明。  
复杂度为 $\Theta(sN\log N)+\Theta(s^2N)=\Theta(sN\log N)=\Theta(s\sigma_0(n)\log\sigma_0(n))$。  
而牛顿迭代并不会增加时间复杂度。

总时间复杂度为：
$$\Theta(T\times\sigma_0(n)(s\log\sigma_0(n)+\log n))$$

# 代码实现

现在的 std 有 BUG，已经确定了是 `poly` 的问题：

`poly` 实现了 多元多项式 exp，我们需要用到它。  
`navie-exp` 是 多元多项式 exp 的朴素实现方法（暴力递推计算），时间复杂度较高，不过你可以对照着调试 bug。
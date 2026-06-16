## DGF 的牛顿迭代

DGF 牛顿迭代的理论基础是**多元多项式的牛顿迭代**。

------------


**记号约定及定义**：

+ $\mathbf x=(x_1,x_2,\cdots,x_m)$；

+ $x_1^{i_1}x_2^{i_2}\cdots x_m^{i_m}$ 称为单项式，其**次数**定义为 $i_1+i_2+\cdots+i_m$；

+ 对于多元多项式 $F(\mathbf x)$，定义其**最低次数**为它所有项中次数的最小值。例如 $xy+y^4+x^3$ 的最低次数为 $2$。

现在，我们来解决多元多项式的牛顿迭代。

> 给定具有简单形式的 $F(x)$，试求多元多项式 $G$，使得 $F(G(\mathbf x))\equiv 0\pmod {\mathbf x^n}$

注：此处 ${}\!\bmod \mathbf x^n$ 的意思是去掉所有次数 $\ge n$ 的项。

考虑倍增，假设我们已经求出了 ${}\!\bmod\mathbf x^n$ 时的解 $G_0$，我们要怎么求得 $G$ 使得 $F(G(\mathbf x))\equiv 0\pmod {\mathbf x^{2n}}$ 呢？

思路和一元多项式的牛顿迭代是一样的，我们考虑 $F$ 在 $G_0$ 处的泰勒展开：

$$F(G(\mathbf x))\equiv F(G_0(\mathbf x))+F'(G_0(\mathbf x))[G(\mathbf x)-G_0(\mathbf x)]+\color{red}\sum_{k=2}^\infty \frac{F^{(k)}(G_0(\mathbf x))}{k!}[G(\mathbf x)-G_0(\mathbf x)]^k$$

因为 $G(\mathbf x)-G_0(\mathbf x)$ 的最低次数是 $n$，所以红色部分在 ${}\!\bmod \mathbf x^{2n}$ 时为 $0$。因此有：

$$F(G_0(\mathbf x))+F'(G_0(\mathbf x))[G(\mathbf x)-G_0(\mathbf x)]\equiv 0\pmod {\mathbf x^{2n}}$$

若 $F'(G_0(\mathbf 0))\neq 0$，则有：

$$G(\mathbf x)\equiv G_0(\mathbf x)-\frac{F(G_0(\mathbf x))}{F'(G_0(\mathbf x))}\pmod {\mathbf x^{2n}}$$

这和一元多项式的式子一模一样。因此，若 $F\circ G$ 能在 $\Theta(n\log n)$ 时间内算出，则多元多项式的牛顿迭代可以在 $\Theta(n\log n)$ 时间内完成。

------------

然后我们来看 DGF 的牛顿迭代，具体而言，我们希望解决如下问题：

> 记数论函数在加法和 Dirichlet 卷积下构成的环为 $R$。给定具有简单形式的 $F(x)\in R[x]$，试求数论函数 $G\in R$，使得 $F(G)=0$。

先给个例子，比如 $F(x)=x-\zeta$，那显然 $F(G)=0$ 的解是 $\zeta$。再比如 $F(x)=x^2-3x+1+\zeta$，则 $G=\frac 32\pm\sqrt{\frac 54-\zeta}$。

下面提供一个在 $\Theta(n\log n\log \log n)$ 时间内求出 $G(1),G(2),\cdots,G(n)$ 的算法。

一个自然的想法是，我们建立从 $R$ 到 $\mathbb C[x_1,x_2,\cdots,x_n,\cdots]$ 的双射 $\rho$，使得对于 $G\in R$，有：

$$\rho(G)=\sum_{n=1}^\infty G(n)\prod_{i=1}^\infty  x_i^{v_{p_i}(n)}$$

注：$v_p(n)=\max\{\beta:p^\beta\mid n\}$。

可以发现，这是两个环之间的同构。也就是说，想要在 $R$ 中求解 $F(G)=0$，我们只需在 $\mathbb C[x_1,\cdots]$ 上求解 $F(H)=0$，且 $G=\rho^{\left<-1\right>}(H)$。

尽管 $\mathbb C[x_1,\cdots]$ 上有无限个未定元，但考虑到我们只关心 $G(1),G(2),\cdots,G(n)$ 的取值，所以我们只看前 $\pi(n)$ 个未定元。

这样，我们就把 DGF 的牛顿迭代问题转化为多元多项式的牛顿迭代问题。当然，实际计算中根本不需要 DGF 转多元多项式，我们只是借助多元多项式这个框架来说明牛顿迭代的适用性。

下面的核心议题是，我究竟要迭代多少次才能正确求出 $G(1),G(2),\cdots,G(n)$。根据前面的推导，每次迭代都会使正确次数翻倍，所以我们只需迭代 $\Theta(\log n)$ 次？事实上，因为 DGF 的特殊性，迭代 $\Theta(\log \log n)$ 就足够了。

具体地讲，想要求出 $G(1),\cdots,G(n)$，我们只需求出 $F(\rho(G))\equiv 0\pmod {\mathbf x^{N+1}}$，其中 $N=\max_{1\le i\le n}\varpi(i)$，$\varpi$ 是质因子个数（计重）。显然 $\varpi$ 在 $2$ 的幂次时取最大值，也即 $N=\lfloor\log_2n\rfloor$。那么最终只需迭代 $\Theta(\log N)=\Theta(\log \log n)$ 次。

假设 $F\circ G$ 能在 $\Theta(n\log n)$ 时间内完成计算，那么我们就得到了一个 $\Theta(n\log n\log\log n)$ 的算法。

## Naszt


第 $k$ 次进行牛顿迭代：  
会得到所有 最高次数 $<2^k$ 的项，记为 $G_{k}$。  
有 $G=G_{\log\log n}$。  
本次会给出 最高次数 $\in[2^{k-1},2^k)$ 的项，记为 $G_{[k]}$。  
有 $G_{k}=G_{k-1}+G_{[k]}=\sum_{i=0}^kG_{[i]}$

那么牛顿迭代的式子就可以写成这样：

$$G_{[k]}=-\frac{F(G_{k-1})}{F'(G_{k-1})}$$

记 $A_{k}$ 为第 $k$ 次进行牛顿迭代中的某一个 DGF 的所有 最高次数 $<2^k$ 的项，$A_{[k]}$ 同理，在计算过程中，我们需要复合 $H(A)$。

若 $[n^{-x}]H(A)$ 的计算只取决于 $\{[n^{-d}]A:d\mid n\}$ 这几个项，我们则可以暴力计算 $A_{[k]}$，因为每次计算只会更新 最高次数 $\in[2^{k-1},2^k)$ 的项，所以每个项只会计算一次。

这样的时间复杂度可以优化到 $\sum_{i=1}^nc\sigma_0(n)=O(cn\log n)$，这其中的 $c$ 绝大部分时候都是常数。  
$c$ 的数值就是计算 $-\frac{F(G_{k-1})}{F'(G_{k-1})}$ 时用到的复合（基本运算）的次数。

| 对比 | 时间复杂度 | 空间复杂度 |
| :----------: | :----------: | :----------: |
| 未加这个优化 | $O(cn\log n\log\log n)$ | $O(n)$ |
| 加了这个优化 | $O(cn\log n)$ | $O(cn)$ |

我觉得这样代码可能会更好写：  
我们没必要真的按照牛顿迭代的方式来写，我们可以对每个元素单独的，按从小到大的顺序来牛顿迭代，因为它的计算只取决于所有的 $A$ 的这几个项：$\{[n^{-d}]A:d\mid n\}$，而这几个项是已知且精确的，所以可以直接牛顿迭代。  
但是如果你这么写，却没有存这么 $c$ 个 $A$，每次都重新计算，时间复杂度会退化到 $O(n\log^3n)$。

---

费稿：

不过我觉得可以再做个优化：

对于一个单项，它需要迭代 $\log$（最高次数） 次。

第一次会计算出 $1$ 次，$a_1(n)\sim\left(\frac1{\zeta(2)}-0\right)n\sim0.6079271019n$ 项。  
第二次会计算出 $3$ 次，$a_2(n)\sim\left(\frac1{\zeta(4)}-\frac1{\zeta(2)}\right)n\sim0.3160113011n$ 项。  
第三次会计算出 $7$ 次，$a_3(n)\sim\left(\frac1{\zeta(8)}-\frac1{\zeta(4)}\right)n\sim0.0720007982n$ 项。  

第 $k$ 次会计算出 $2^k-1$ 次，$a_k(n)\sim\left(\frac1{\zeta(2^k)}-\frac1{\zeta(2^{k-1})}\right)n<0.5^{2^k}n$ 项。  


---
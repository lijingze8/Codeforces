# Codeforces Round 363 Div. 1 #

## A. Vacations (1s, 256MB) ##

**题目大意：**给定连续 $n$ 天，每天为如下四种状态之一：

  * 不能进行运动或比赛
  * 可以进行运动但不能比赛
  * 可以进行比赛但不能运动
  * 可以进行比赛或运动
  
对于每天，可以根据当天的状态选择运动，比赛或休息。但不能连续两天的选择均为运动或均为比赛。求在这 $n$ 天中最少需要休息多少天。

**数据范围：**$n \leq 100$

**简要题解：**令 $f_{i,0},f_{i,1},f_{i,2}$ 分别表示考虑了前 $i$ 天，且最后一天为运动，比赛和休息时最少需要休息的天数。显然可以从状态 $f_{i-1,0},f_{i-1,1},f_{i-1,2}$ 转移过来。

**时空复杂度：**$O(n) - O(n)$

**关键字：**动态规划

## B. Fix a Tree (2s, 256MB) ##

**题目大意：**对于一个可以表示有根树的数列 $\{p_n\}$，其有：

  * 数列中有且仅有一项 $r$ 满足 $p_r=r$，即为根
  * 其他的 $n-1$ 项表示结点 $i$ 和结点 $p_i$ 间有一条边
  
现给定数列 $\{a_n\}$，求至少要改变其中的多少项，才能使 $\{a_n\}$ 能表示一棵有根树。

**数据范围：**$2 \leq n \leq 2 \times 10^5$，$1 \leq a_i \leq n$

**简要题解：**不妨先在所有的 $i$ 和 $a_i$ 间连一条边，那么生成的图为一些边和一些环（包括自环）。如果存在 $r$ 使得 $a_r=r$，则令 $r$ 为根即可，否则可以任意选择一个结点作为根。而当根 $r$ 确定后，只要将环中的任意一个结点所连出的边改为连向根 $r$ 即可。具体实现可以借助并查集。

**时空复杂度：**$O(n \alpha (n)) - O(n)$

**关键字：**并查集，图论

## C. LRU (2s, 256MB) ##

**题目大意：**有 $n$ 个视频和一个可以存放 $k$ 个视频的缓存区。在每次操作中，第 $i$ 个视频将有 $p_i$ 的概率会被选中，若被选中的视频不在缓存区中，则将其加入缓存区。如果缓存区已满，则将最早加入的视频移出，将被选中视频加入。求经过 $10^{100}$ 次操作后各个物品在缓存区中的概率。

**数据范围：**$1 \leq k \leq n \leq 20$

**解法一：**注意到最后一次加入的视频必定在缓存区中，而第一次加入的视频几乎对结果没有任何影响，所以我们可以倒过来考虑这些操作。令 $g_{ij}$ 为第 $i$ 个视频被倒数第 $j$ 个加入的概率，则第 $i$ 个视频最终在缓冲区中的概率 $ans_i=\sum_{j=1}^k g_{ij}$。可以考虑用状态压缩动态规划来解决这个问题。令 $a_i$ 表示 $i$ 的二进制表示中 $1$ 的个数，令 $f_i$ 表示倒数加入 $a_i$ 个视频后缓存区中视频存在状态为 $i$ （$i$ 中的 $1$ 表示在缓存区中）的概率，令 $s_i=\sum_{j=0}^{n-1} [i~\verb>&>~2^j= 0] \times p_j$，即当前未在缓存区中的视频的被选中概率之和，那么转移方程为
$$f_{i+2^j}=f_{i+2^j}+f_i \times \frac{p_j}{s_i}~~(i~\verb>&>~2^j= 0)$$
转移的同时将答案 $ans_j$ 更新即可。

**时空复杂度：**$O(n2^n) - O(2^n)$

**解法二：**可以依次计算第 $i$ 个视频最终在缓存区中的概率。考虑视频 $i$，设当其最后一次被选中后，又进行了 $x$ 次选择操作。若最终视频 $i$ 在缓冲区中，那么这 $x$ 次操作最多涉及到 $k-1$ 种不同的视频。考虑任意一个含有 $k-1$ 种视频的集合 $S$（不能包括视频 $i$），令集合 $S$ 中所有视频的被选中概率之和为 $P_S$，则上面这些情况发生的概率为 $p_i+p_i \times P_S+p_i \times P_S^2+\cdots+p_i \times P_S^x$，当 $x \rightarrow \infty$ 时，其等于 $\frac{p_i}{1-P_S}$。若枚举所有的 $S$，将概率累加，会发现含有 $k-2,k-3,\cdots$ 种不同视频的情况会被重复计算多次。于是再枚举含有 $k-2$ 种视频的集合 $S'$，考虑到其概率在枚举所有的 $S(S' \subseteq S)$ 时均被计算了一次，故将其减去 $C_{(n-1)-(k-2)}^{(k-1
)-(k-2)}$ 次即可。接下来再枚举含有 $k-3$ 种视频的集合 $S''$，依次类推。注意到这是一个容斥的过程，可以预处理出容斥的系数，计算时直接调用即可。

**时空复杂度：**$O(n2^n) - O(2^n)$

**关键字：**概率论，动态规划，容斥原理

## D. Limak and Shooting Points (3s, 256MB) ##

**题目大意：**有 $k$ 块传送石位于 $(ax_i,ay_i)$ 和 $n$ 个怪物位于 $(mx_i,my_i)$，保证这 $k+n$ 个位置互不相同。可以在传送石位置向任意方向射箭，箭会攻击到该方向上的第一个怪物，同时怪物和箭均会消失。现在可以以任意顺序利用这 $k$ 块传送石向任意方向射箭，但在每块传送石处只能射出一箭，求有多少怪物可能被射到。

**数据范围：**$1 \leq k \leq 7$，$1 \leq n \leq 1000$，$-10^9 \leq ax_i,ay_i,mx_i,my_i \leq 10^9$

**简要题解：**枚举所有利用传送石顺序的排列 $P$，检验是否能以该顺序使用传送石来射中怪物 $i$。具体用递归来进行判断。令状态 $(j,s)$ 表示正在使用第 $P_j$ 个传送石，当前要射击的怪物集合为 $s$，初始时 $s=\{i\}$。每次认为将要在 $P_j$ 处射到 $s$ 中的第一个怪物 $s_1$，但可能在该方向上存在其余怪物 $t_1,t_2,\cdots,t_m$ 遮挡住 $P_j$ 射向 $s_1$ 的箭，故接下来这些怪物将要被射掉。于是转移到状态 $(j+1,s')$ 继续进行上述过程，其中 $s'=s-\{s_1\}+\{t_1,t_2,\cdots,t_m\}$，当 $s'$ 为空时，说明怪物 $i$ 可以被射到。

**时空复杂度：**$O(k! \cdot nlogn) - O(kn)$

**关键字：**极角排序，模拟，搜索

## E. Cron (3s, 256MB) ##

**题目大意：**给定 $s,m,h,day,date,month$ 参数用以描述一个工作时刻，其中 $s$ 为秒，$m$ 为分钟，$h$ 为小时，$day$ 为星期几，$date$ 为日，$month$ 为月。当其中有 $-1$ 时表示该参数可以为任意值，当 $day$ 和 $date$ 同时不为 $-1$ 时认为两者任一可以为任意值。假定当前时刻为 `00:00:00 January 1st, 1970 (Thursday)`。现有 $n$ 个询问 $t_i$，对于每个询问，求 $t_i$ 秒后第一个工作时刻距当前时刻多少秒。

**数据范围：**$0 \leq s,m \leq 59$，$0 \leq h \leq 23$，$1 \leq day \leq 7$，$1 \leq date \leq 31$，$1 \leq month \leq 12$，$n \leq 1000$，$0 \leq t_i \leq 10^{12}$

**简要题解：**注意到参数 $s,m,h$ 以每天为一个周期，参数 $day,date,month$ 以每 $400$ 年为一个周期。考虑将这两种周期中符合条件的时刻按顺序记录下来，对于每个询问直接在这些时刻中二分即可。

**时空复杂度：**$O(2.5 \times 10^5+nlog(1.5 \times 10^5)) - O(2.5 \times 10^5)$

**关键字：**模拟

## F. Coprime Permutation (2s, 256MB) ##

**题目大意：**构造一个排列 $p_1,p_2,\cdots,p_n$ 满足：
$$\forall_{1 \leq i < j \leq n} (i,j)=1 \iff (p_i,p_j)=1$$
现已知 $p$ 中一些位置的值，求有多少种构造方案。

**数据范围：**$2 \leq n \leq 10^6$

**简要题解：**先不考虑有些位置值已经确定的情况。定义 $f(a)=\{a,2a,\cdots,ma\}$，其中 $(m+1)a>n$。注意到排列 $1,2,\cdots,n$ 即为一个满足条件的排列，且其余满足条件的排列必可由该排列通过以下变换得到：

  * **变换一：**若数 $i$ 和 $j$ 含有相同的质因子，则 $i,j$ 可以互换位置
  * **变换二：**若存在质数 $a,b$ 满足 $\biggl\lfloor\dfrac{n}{a}\biggr\rfloor=\biggl\lfloor\dfrac{n}{b}\biggr\rfloor$，即存在 $f(a)$ 和 $f(b)$ 一一对应，则可以将对应的数互换位置
  
可以发现，$1,2,\cdots,n$ 经过以上两种变换成为新的排列 $p$ 后，$p$ 应具有以下性质：

  * $i$ 和 $p_i$ 的质因子数相等
  * 注意到变换二中的 $a,b$ 必然大于 $\sqrt{n}$，从而 $i$ 和 $p_i$ 小于 $\sqrt{n}$ 的质因子对应相等，且大于 $\sqrt{n}$ 的质因子满足变换二中的条件
  * 对于质数 $a,b,c$ 满足 $\biggl\lfloor\dfrac{n}{a}\biggr\rfloor=\biggl\lfloor\dfrac{n}{b}\biggr\rfloor=\biggl\lfloor\dfrac{n}{c}\biggr\rfloor$，则 $f(a)$ 中的数不能同时出现在 $f(b),f(c)$ 中数的位置上，且在 $f(a)$ 中数的位置上不能同时出现 $f(b),f(c)$ 中的数
  
有了以上性质，对于某些位置的数已经确定的情况，可以很快判断出是否无解。然后阶乘统计答案即可。注意考虑 $1$ 的情况。

**时空复杂度：**$O(nlogn) - O(n)$

**关键字：**结论，数论，排列组合

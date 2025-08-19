$$a^b\equiv 
\begin{cases}
a^{b\bmod \varphi(m)} & \gcd(a,m)=1 \\
a^{b} & \gcd(a,m)\not=1,b<\varphi(m) \\
a^{(b\bmod \varphi(m))+\varphi(m)} & \text{otherwise}
\end{cases}
\pmod m
$$
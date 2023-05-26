## NineNine
### 关于背景
这应该是我很久以前在一个**Minecraft游戏视频**上看到的棋，我当时印象很深刻（游戏并非原创）<br>
但我发现我周围从来没有人知道这种棋，它看起来就像是**一个天才一时兴起发明的一个小游戏**<br>
在高中时，我把这个游戏介绍给了同学，跟他们在草稿纸上厮杀了很多局<br>
现在，我用**代码实现**这款游戏<br>
### 游戏规则
#### 1. 棋盘
棋盘由**九个九宫格**构成，棋盘编号如图，格子序号与棋盘顺序一致<br>
*如5.5表示中间那块棋盘的中间位置*<br>
[![棋盘图.png](https://img1.imgtp.com/2023/05/26/8Q3H6LL1.png)](https://img1.imgtp.com/2023/05/26/8Q3H6LL1.png)<br>
#### 2. 落子
**先手方第一回合**在**中间棋盘**的九个位置中落子，随后双方按如下规则轮流落子：<br>
若对方落子在 x.y 号位（x 号棋盘 y 号位置），则本回合我方只能在 y 号棋盘上落子<br>
[![落子规则.png](https://img1.imgtp.com/2023/05/26/VVtzXVcs.png)](https://img1.imgtp.com/2023/05/26/VVtzXVcs.png)<br>
上图中，先手方蓝色在 5.6 落子，故后手黄色方接下来要在 6 号棋盘落子<br><br>
注意：若对方的落子指向了被**占领**的棋盘或者**无处可下**的棋盘，则无视上述规则，任意可下棋盘均可落子<br>
[![指向被占领的棋盘.png](https://img1.imgtp.com/2023/05/26/Rkq3eO8Z.png)](https://img1.imgtp.com/2023/05/26/Rkq3eO8Z.png)<br>
*5 号棋盘被占领的情况下，黄色方依旧下在 5 号位，则蓝色方接下来任意落子*<br>
*游戏中可以落子的棋盘会以**箭头**标出*<br>
#### 3. 占领
任何一个棋盘上，当有一方**三子连线**（横竖斜）后，称该棋盘被这一方**占领**<br>
棋盘被任何一方占领后立即**锁死，不允许任何落子**<br>
[![小棋盘占领.png](https://img1.imgtp.com/2023/05/26/hCilHg42.png)](https://img1.imgtp.com/2023/05/26/hCilHg42.png)<br>
*5 号棋盘被蓝色方占领*<br>
#### 4. 获胜
任何一方占领的棋盘连成一条线后，该方获胜，游戏结束<br>
[![获胜图.png](https://img1.imgtp.com/2023/05/26/5R04owSs.png)](https://img1.imgtp.com/2023/05/26/5R04owSs.png)<br>
*蓝色方获胜*<br>
### ORIGIN
这个文件夹中包含了

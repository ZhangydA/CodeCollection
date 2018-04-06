#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
const int maxn = 50;

map< string,vector<string> >NFA;
vector<string>DFA[maxn];
map<string,char>mp; ///重名的使用
set<char>A; /// 表示给了一个 a 后的状态
set<char>B; /// 表示给了一个 b 后的状态
int cnt = 0; ///表示第cnt个重命名
set<string>st1; ///检查是否出现重复的    NO
queue<string>Q; ///保证顺序

void Read_NFA(){
    string str,a,b;
    while (true){
        cin >> str >> a >> b;
        vector<string>vec;
        vec.push_back(a);
        vec.push_back(b);
        NFA["{" + str + "}"] = vec;
        if (str == "f") break;
    }
}

string getString(set<char> &S,int t,char temp){
    ///cout << "输出集合的大小" << " " << S.size() << endl;
    string result;
    string ch = "{ }";
    ch[1] = temp;
    string buf = NFA[ch][t];
    int flag = 0;
    if (buf == "{NULL}") return "";
    for(int j = 1;j <= buf.size() - 2;j ++){
        if (buf[j] == ',') continue;
        if (!S.count(buf[j])){
            S.insert(buf[j]);
            if (flag == 0){
                result.push_back(buf[j]);
                flag = 1;
            } else {
                result.push_back(',');
                result.push_back(buf[j]);
            }
        }
    }
    return result;
}

void IsInQueue(string str){
    if (!st1.count(str) && str != "{NULL}" && str != "{}"){
        st1.insert(str);
        ///cout << "进入队列" << " " << str << endl;
        Q.push(str);
    }
}

void ConvetToDFA(){
    ///初始状态
    string str = "{0}";
    Q.push(str); st1.insert(str);
    while (!Q.empty()){ ///进入队列中的一定是没有出现过的
        string temp = Q.front();  Q.pop();
        ///cout << "temp = " << temp << endl;
        string a = "{",b = "{",ming;
        mp[temp] = 'A' + cnt;
        ///为字符串进行重命名
        DFA[cnt].push_back(temp);
        ming.push_back('A' + cnt);
        DFA[cnt].push_back(ming);
        ///如果内部只有一个元素说明在NFA中已经包含直接放进去即可
        if (NFA.count(temp)) {
            a = NFA[temp][0];
            b = NFA[temp][1];
            DFA[cnt].push_back(a);
            DFA[cnt].push_back(b);
            IsInQueue(a);
            IsInQueue(b);
        } else {
            A.clear(); B.clear();
            int flaga = 0,flagb = 0;
            for (int i = 1;i <= temp.size() - 2;i ++){
                if (temp[i] == ',') continue;
                string a1 = getString(A,0,temp[i]);
                if (a1 != ""){
                    if (flaga == 0) flaga = 1;
                    else a.push_back(',');
                }
                a += a1;
                string a2 = getString(B,1,temp[i]);
                if (a2 != ""){
                    if (flagb == 0) flagb = 1;
                    else b.push_back(',');
                }
                b += a2;
            }
            a += "}"; b += "}";
            DFA[cnt].push_back(a);
            DFA[cnt].push_back(b);
            IsInQueue(a);
            IsInQueue(b);
        }
        cnt ++;
    }
}

void Print(){
    for (int i = 0;i < cnt;i ++){
        for (int j = 0;j < DFA[i].size();j ++){
            if(j > 1){
                if (mp.count(DFA[i][j])) cout << mp[DFA[i][j]];
            } else cout << DFA[i][j];
        }
        cout << endl;
    }
}

void MainPort(){
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃            使用说明           ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   0.返回主程序                ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   1.样例输入输出格式说明      ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   2.一组简短的测试样例(参考)  ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   3.输入自己的数据            ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   4.结束程序运行              ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void ReturnMainPort(){
    int m;
    while (scanf ("%d",&m) == 1){
        if (m == 0){
            system("cls");
            MainPort();
            break;
        }
        else printf ("输入错误请重新输入:");
    }
}

void PrintStaue(){
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃   样例输入说明                                       ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   1.第一列表示状态名，终状态用f表示                  ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   2.第二列和第三列分别表示输入字符a和b所到达的状态   ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   样例输出说明                                       ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   1.第一列表示输入状态名                             ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   2.第二列表示重新命名的状态名                       ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   3.第三列和第四列分别表示输入字符a和b所到达的状态   ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("后退请输入0:\n");
    ReturnMainPort();
}

void PrintCodeStander(){
    int m;
    printf ("样例输入:\n");
    printf ("0 {1} {0,1}\n1 {2} {NULL}\n2 {2,f} {f}\nf {NULL} {NULL}\n");
    printf ("样例输出:\n");
    printf ("{0}ABC\n{1}BD\n{0,1,}CEC\n{2}DFG\n{2,f,}FFG\n{f}G\n");
    printf("后退请输入0:\n");
    ReturnMainPort();

}

void Execute(){
    int m;
    printf("请按照要求输入您的数据:\n");
    Read_NFA();
    ConvetToDFA();
    printf ("输出结果\n");
    Print();
    printf("\n是否继续(1:继续输入  0:结束输入):");
    cin >> m;
    if (m == 1){
        system("cls");
        Execute();
    }
    return ;
}

int main(){
    int n,m;
    MainPort();
    printf ("请输入选择的模式:");
    while (cin >> n){
        if (n == 1){
            system("cls");
            PrintStaue();
        } else if (n == 2){
            system("cls");
            PrintCodeStander();
        } else if (n == 3){
            system("cls");
            Execute();
            printf("谢谢使用\n");
            return 0;
        } else if (n == 4){
            system("cls");
            printf("谢谢使用\n");
            return 0;
        } else {
            printf ("输入错误请按照说明重新输入:");
        }
    }
    return 0;
}

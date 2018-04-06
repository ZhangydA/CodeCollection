#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
const int maxn = 50;

map< string,vector<string> >NFA;
vector<string>DFA[maxn];
map<string,char>mp; ///������ʹ��
set<char>A; /// ��ʾ����һ�� a ���״̬
set<char>B; /// ��ʾ����һ�� b ���״̬
int cnt = 0; ///��ʾ��cnt��������
set<string>st1; ///����Ƿ�����ظ���    NO
queue<string>Q; ///��֤˳��

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
    ///cout << "������ϵĴ�С" << " " << S.size() << endl;
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
        ///cout << "�������" << " " << str << endl;
        Q.push(str);
    }
}

void ConvetToDFA(){
    ///��ʼ״̬
    string str = "{0}";
    Q.push(str); st1.insert(str);
    while (!Q.empty()){ ///��������е�һ����û�г��ֹ���
        string temp = Q.front();  Q.pop();
        ///cout << "temp = " << temp << endl;
        string a = "{",b = "{",ming;
        mp[temp] = 'A' + cnt;
        ///Ϊ�ַ�������������
        DFA[cnt].push_back(temp);
        ming.push_back('A' + cnt);
        DFA[cnt].push_back(ming);
        ///����ڲ�ֻ��һ��Ԫ��˵����NFA���Ѿ�����ֱ�ӷŽ�ȥ����
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
    printf("������������������������������������������������������������������\n");
    printf("��            ʹ��˵��           ��\n");
    printf("�ǩ���������������������������������������������������������������\n");
    printf("��   0.����������                ��\n");
    printf("�ǩ���������������������������������������������������������������\n");
    printf("��   1.�������������ʽ˵��      ��\n");
    printf("�ǩ���������������������������������������������������������������\n");
    printf("��   2.һ���̵Ĳ�������(�ο�)  ��\n");
    printf("�ǩ���������������������������������������������������������������\n");
    printf("��   3.�����Լ�������            ��\n");
    printf("�ǩ���������������������������������������������������������������\n");
    printf("��   4.������������              ��\n");
    printf("������������������������������������������������������������������\n");
}

void ReturnMainPort(){
    int m;
    while (scanf ("%d",&m) == 1){
        if (m == 0){
            system("cls");
            MainPort();
            break;
        }
        else printf ("�����������������:");
    }
}

void PrintStaue(){
    printf("����������������������������������������������������������������������������������������������������������������\n");
    printf("��   ��������˵��                                       ��\n");
    printf("�ǩ�������������������������������������������������������������������������������������������������������������\n");
    printf("��   1.��һ�б�ʾ״̬������״̬��f��ʾ                  ��\n");
    printf("�ǩ�������������������������������������������������������������������������������������������������������������\n");
    printf("��   2.�ڶ��к͵����зֱ��ʾ�����ַ�a��b�������״̬   ��\n");
    printf("�ǩ�������������������������������������������������������������������������������������������������������������\n");
    printf("��   �������˵��                                       ��\n");
    printf("�ǩ�������������������������������������������������������������������������������������������������������������\n");
    printf("��   1.��һ�б�ʾ����״̬��                             ��\n");
    printf("�ǩ�������������������������������������������������������������������������������������������������������������\n");
    printf("��   2.�ڶ��б�ʾ����������״̬��                       ��\n");
    printf("�ǩ�������������������������������������������������������������������������������������������������������������\n");
    printf("��   3.�����к͵����зֱ��ʾ�����ַ�a��b�������״̬   ��\n");
    printf("����������������������������������������������������������������������������������������������������������������\n");
    printf("����������0:\n");
    ReturnMainPort();
}

void PrintCodeStander(){
    int m;
    printf ("��������:\n");
    printf ("0 {1} {0,1}\n1 {2} {NULL}\n2 {2,f} {f}\nf {NULL} {NULL}\n");
    printf ("�������:\n");
    printf ("{0}ABC\n{1}BD\n{0,1,}CEC\n{2}DFG\n{2,f,}FFG\n{f}G\n");
    printf("����������0:\n");
    ReturnMainPort();

}

void Execute(){
    int m;
    printf("�밴��Ҫ��������������:\n");
    Read_NFA();
    ConvetToDFA();
    printf ("������\n");
    Print();
    printf("\n�Ƿ����(1:��������  0:��������):");
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
    printf ("������ѡ���ģʽ:");
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
            printf("ллʹ��\n");
            return 0;
        } else if (n == 4){
            system("cls");
            printf("ллʹ��\n");
            return 0;
        } else {
            printf ("��������밴��˵����������:");
        }
    }
    return 0;
}

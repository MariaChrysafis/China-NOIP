#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
#include <queue>
#include <cmath>
#include <map>
#include <stack>
#include <ctime>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    int myMax = -1;
    string best = "";
    int tot = 0;
    while (t--) {
        string name;
        cin >> name;
        int average_grade, class_evaluation;
        string student_leader, western_province;
        int papers;
        cin >> average_grade >> class_evaluation >> student_leader >> western_province >> papers;
        bool academian = (average_grade > 80 && papers >= 1);
        bool may = (average_grade > 85 && class_evaluation > 80);
        bool excellence = (average_grade > 90);
        bool western = (average_grade > 85 && western_province == "Y");
        bool class_contribution = (class_evaluation > 80 && student_leader == "Y");
        int money = 8000 * academian + 4000 * may + 2000 * excellence + 1000 * western + 850 * class_contribution;
        if (money > myMax) {
            best = name;
            myMax = money;
        }
        tot += money;
    }
    cout << best << '\n';
    cout << myMax << '\n';
    cout << tot << '\n';
}

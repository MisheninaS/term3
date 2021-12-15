#include <iostream>
#include <vector>
using namespace std;

struct Member{
    int time_stamp;
    int id;
    float vit_d;
    float acat;
    float anti_tg;
    vector<float> neural_activity;
    float mcr;
    float difference;
};

Member create_member(int t, int i, float v, float a1, float a2, float n, float m) {
    Member member;
    member.time_stamp = t;
    member.id = i;
    member.vit_d = v;
    member.acat = a1;
    member.anti_tg = a2;
    member.neural_activity = {n};
    member.mcr = m;
    member.difference = 0;
    return member;
}

int find_id(vector<Member> mem, int new_id){
    for (int i = 0; i < mem.size(); i++){
        if (mem[i].id == new_id) {
            return i;
        }
    }
    return -1;
}

float diff(Member mem) {
    if (mem.neural_activity.size() == 0) {
        return -1;
    } else {
        float nmax = mem.neural_activity[0];
        float nmin = mem.neural_activity[0];
        for (int i = 0; i < mem.neural_activity.size(); i++){
            if (mem.neural_activity[i] > nmax) {
                nmax = mem.neural_activity[i];
            }
            if (mem.neural_activity[i] < nmin) {
                nmin = mem.neural_activity[i];
            }
        }
        return (nmax - nmin);
    }
}

vector<Member> bubble_sort(vector<Member> a) {
    for (int k = 0; k < a.size(); ++k) {
        for (int i = 0; i < a.size() - 1; ++i) {
            if (a[i].difference > a[i + 1].difference) {
                Member t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            }
        }
    }
    return a;
}

vector<Member> bubble_sort2(vector<Member> a) {
    for (int k = 0; k < a.size(); ++k) {
        for (int i = 0; i < a.size() - 1; ++i) {
            if (a[i].id > a[i + 1].id) {
                Member t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            }
        }
    }
    return a;
}

int main(){
    int num;
    cin >> num;
    vector<Member> members;
    for (int i = 0; i < num; i++) {
        int t_, i_;
        float v_, a1_, a2_, n_, m_;
        cin >> t_ >> i_ >> v_ >> a1_ >> a2_ >> n_ >> m_;
        if (members.size() == 0) {
            Member first_member;
            first_member = create_member(t_, i_, v_, a1_, a2_, n_, m_);
            members.push_back(first_member);
        } else {
            if (find_id(members, i_) == -1) {
                Member next_member;
                next_member = create_member(t_, i_, v_, a1_, a2_, n_, m_);
                members.push_back(next_member);
            } else {
                members[find_id(members, i_)].neural_activity.push_back(n_);
            }
        }
    }
    int k = 0;
    while (k < members.size()) {
        if (members[k].neural_activity.size() != 1) {
            members[k].difference = diff(members[k]);
            k++;
        } else {
            members.erase(members.begin() + k);
        }
    }
    members = bubble_sort(members);
    if (members.size() == 0) {
        cout << -1;
    } else if (members.size() > 3) {
        members.erase(members.begin() + 3, members.end());
        members = bubble_sort2(members);
        for (int i = 0; i < 3; i++) {
            cout << members[i].id << " ";
        }
    } else {
        members = bubble_sort2(members);
        for (int i = 0; i < members.size(); i++) {
            cout << members[i].id << " ";
        }
    }
}




#include <iostream>
#include <string.h>
using namespace std;

struct Date{
    int d;
    int m;
    int y;
};
struct Date_with_num{
    Date dt;
    int nm;
};

Date create_date(string str_date) {
    Date date;
    int dd = (int(str_date[0]) - 48)*10 + (int(str_date[1]) - 48);
    int mm = (int(str_date[3]) - 48)*10 + (int(str_date[4]) - 48);
    int yyyy =  (int(str_date[6]) - 48)*1000 + (int(str_date[7]) - 48)*100 + (int(str_date[8]) - 48)*10 + (int(str_date[9]) - 48);
    date.d = dd;
    date.m = mm;
    date.y = yyyy;
    return date;
}
Date_with_num create_date_with_num(Date date, int num) {
    Date_with_num date_with_num;
    date_with_num.dt = date;
    date_with_num.nm = num;
    return date_with_num;
};

void print_date(Date d){
    cout << d.d << "." << d.m << "." << d.y;
}

Date min_date(Date d1, Date d2) {
    if (d1.y < d2.y) {
        return d1;
    } else if (d2.y < d1.y) {
        return d2;
    }
    if (d1.m < d2.m) {
        return d1;
    } else if (d2.m < d1.m) {
        return d2;
    }
    if (d1.d < d2.d) {
        return d1;
    } else if (d2.d < d1.d) {
        return d2;
    }
    return d1;
}

bool eq_dates(Date d1, Date d2) {
    if ((d1.d == d2.d) && (d1.m == d2.m) && (d1.y == d2.y)) {
        return true;
    } else {
        return false;
    }
}

int main(){
    int n;
    int sum = 0;
    cin >> n;
    Date_with_num* dates = new Date_with_num[n];
    for (int i = 0; i < n; i++) {
        string date;
        cin >> date;
        Date date_without_num = create_date(date);
        int num;
        cin >> num;
        //int int_num = int(num[0]) - 48;
        dates[i] = create_date_with_num(date_without_num, num);
    }
    int m;
    cin >> m;
    int* num2 = new int[m];
    Date* dates2 = new Date[m];
    for (int i = 0; i < m; i++) {
        string date2;
        cin >> date2;
        dates2[i] = create_date(date2);
    }
    for (int i = 0; i < m; i++) {
        num2[i] = 0;
        for (int j = 0; j < n; j++) {
            if (eq_dates(min_date(dates2[i], dates[j].dt), dates[j].dt)) {
                if (dates[j].nm > num2[i]) {
                    num2[i] = dates[j].nm;
                }
                //num2[i] = num2[i] + dates[j].nm;
                //cout << dates[j].nm << "\n";
            }
        }
    }
    //for (int i = 0; i < m; i++) {
        //cout << num2[i] << "\n";
    //}
    for (int i = 0; i < m; i++) {
        cout << num2[i] << "\n";
    }
}

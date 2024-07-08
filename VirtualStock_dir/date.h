#ifndef DATE_H
#define DATE_H


class Date {
public:
    Date();
    Date(int year, int month) : year(year), month(month) {
        normalize();
    }

    // 获取年份
    int getYear() {
        return year;
    }

    // 获取月份
    int getMonth(){
        return month;
    }

    // 增加月份
    void addMonths(int months) {
        month += months;
        normalize();
    }

    // 减少月份
    void subtractMonths(int months) {
        month -= months;
        normalize();
    }

    // 时间推移函数，每次调用时按指定周期推移日期
    void advance(int period) {
        addMonths(period);
    }

    // 比较两个日期是否相等
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month;
    }

    // 比较两个日期是否不相等
    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    // 比较两个日期的大小
    bool operator<(const Date& other) const {
        if (year < other.year) return true;
        if (year > other.year) return false;
        return month < other.month;
    }

    bool operator>(const Date& other) const {
        return other < *this;
    }

    bool operator<=(const Date& other) const {
        return !(other < *this);
    }

    bool operator>=(const Date& other) const {
        return !(*this < other);
    }

private:
    int year=2023;
    int month;

    // 规范化日期
    void normalize() {
        while (month > 12) {
            month -= 12;
            ++year;
        }
        while (month < 1) {
            month += 12;
            --year;
        }
    }
};




#endif // DATE_H

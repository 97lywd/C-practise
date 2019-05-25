#include<iostream>;
#include<stdlib.h>;
using namespace std;
class Date
{
    public:
	Date(int year = 1900, int month = 1, int day = 1)  //构造函数
	{
		if (year <= 0 || month <= 0 || month > 12 || day <= 0 || day > GetDay(year,month))
		{
			cout << "日期非法，已修改为默认日期1999-1-1" << endl;
			_year = 1999;
			_month = 1;
			_day = 1;
		}
		 _year = year;
		 _month = month;
		 _day = day;
	}
	//int sumdays(Date& d)    //判断多少天
	//{
	//	int sumdays = 0;
	//	for (int i = 1; i < d._month; i++)
	//	{
	//		sumdays += d.Getday(d._year, i);
	//	}
	//	sumdays += d._month;
	//	return sumdays;
	//}
	Date(const Date& d)      //拷贝构造
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	Date& operator=(const Date &d) // =重载
	{
		if (this != &d)
		{
			_year = d._year;
			_day = d._day;
			_month = d._month;
		}
		return *this;
	}
	Date& operator+=(int day)   //>=重载
	{
		_day += day;
		while (_day > GetDay(_year, _month))
		{
			_day -= GetDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_month = 1;
				_year++;
			}
		}
		return *this;
	}
	Date& operator-=(int day)   //-=重载
	{
		_day -= day;
		while (_day <= 0)
		{
			_day += GetDay(_year, _month);
			_month--;
			if (_month < 1)
			{
				_month = 12;
				_year--;
			}
		}
		return *this;
	}
	int GetDay(int year, int month)
	{
		int day[] = { 31,28,31,30,31,30,31,30,30,31,30,31 };
			if (month = 2)
			{
				if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
				{
					day[1] = 29;
				}
			}
			return day[month];
	}
	bool operator>(const Date& d)const   //d1 > d2
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month > d._month)
			{
				return true;
			}
			else if (_month > d._month) {
				if (_day > d._day) {  
					return true;
				}
			}
		}
		return false;
	}
	bool operator==(const Date& d)const {
		return (_year == d._year) && (_month == d._month) && (_day == d._day);
	}
	bool operator!=(const Date& d)const {
		return !(*this == d);
	}
	bool operator>=(const Date& d)const
	{
		return((*this > d) || (*this ==d));
	}
	bool operator<(const Date& d)const
	{
		return !(*this >= d);
	}
	bool operator<=(const Date&d)const {
		return !(*this > d);
	}
	void print()
	{
		cout << _year <<"-"<< _month <<"-"<< _day << endl;
	}
    private:
	  int _year;
	  int _month;
	  int _day;

};

int main()
{
	Date d1(2018, 1, 1);
	Date d2(2019, 1, 1);
	//cout << (d1.SumDays) << endl;
	cout << "d1 += 10:" << endl;
	d1 += 10;
	d1.print();
	cout << "d2 -= 10:" << endl;
	d2 -= 10;
	d2.print();
	cout << (d1 > d2) << endl;
	cout << (d1 >= d2) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;
	cout << (d1 < d2) << endl;
	system("pasue");
	return 0;
}

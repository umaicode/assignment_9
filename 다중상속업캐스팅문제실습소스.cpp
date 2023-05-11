//operator<<() 실행후 소멸자가 호출되는 문제 파악을 위한 Coder클래스의 cout 연산자에 디버깅 설정후 F11으로 실행 확인하여 원인 파악
// (Employee &) cd 등으로 참조 변수로 upcasting하여 소멸자 호출을 방지하는 것이 필요

#include <iostream>
#include <string>
using namespace std;
class Dept {
	string dname;
	string city;
public:
	Dept(string d, string c) : dname(d), city(c) {}
	int operator>(Dept&);
	friend ostream& operator<<(ostream&, Dept&);
};

ostream& operator<<(ostream& s, Dept& d) {
	s << "dname = " << d.dname << ", city = " << d.city;
	return s;
}
class Person {
private:
	string pid;
	string pname;
	friend ostream& operator<<(ostream&, Person&);
public:
	Person(string pid, string pname) : pid(pid), pname(pname) {}
	~Person() { cout << "Person:: 소멸자 호출됨" << endl; }
};
ostream& operator<<(ostream& s, Person& p) {
	s << "pid = " << p.pid << ", pname = " << p.pname << endl;
	return s;
}
class Employee : virtual public Person {
private:
	string eno;
	Dept* dname;
public:
	Employee(string eno, string dname, string city, string pid, string pname) : Person(pid, pname), eno(eno) { this->dname = new Dept(dname, city); }
	~Employee() { delete dname; cout << "Employee:: 소멸자 호출됨" << endl; }
	friend ostream& operator<<(ostream&, Employee&);
};

ostream& operator<<(ostream& s, Employee& e) {
	s << "eno = " << e.eno << ", " << (*e.dname) << ", " << (Person&)e;
	return s;
}
class Student : virtual public Person {
private:
	string sid;
	Dept* dname;
	friend ostream& operator<<(ostream&, Student&);
public:
	Student(string sid, string dname, string city, string pid, string pname) : Person(pid, pname), sid(sid) {
		this->dname = new Dept(dname, city);
	}
	~Student() {
		delete dname; cout << "Student:: 소멸자 호출됨" << endl;
	}

};
ostream& operator<<(ostream& s, Student& st) {
	s << "sid = " << st.sid << (*st.dname) << (Person)st;
	return s;
}
class Coder : public Employee {
private:
	string language;
	double workYears;
public:
	Coder(string language, double workYears, string eno, string dname, string city, string pid, string pname) : Person(pid, pname), Employee(eno, dname, city, pid, pname) {
		this->language = language;
		this->workYears = workYears;
	}
	~Coder() { cout << "Coder:: 소멸자 호출됨" << endl; } // Employee::destructor(); 
	friend ostream& operator<<(ostream&, Coder&);
};



ostream& operator<<(ostream& s, Coder& c) {
	s << "language = " << c.language << ", workyears = "
		<< c.workYears << ", " << (Employee&)c;
	return s;
}
class PartTimeStudent : public Employee, public Student {
private:
	double salary;
	double grade;

public:
	PartTimeStudent(double salary, double grade, string eno, string sid, string dname, string city, string pid, string pname) :
		Person(pid, pname), Employee(eno, dname, city, pid, pname),
		Student(sid, dname, city, pid, pname), salary(salary), grade(grade) {}
	friend ostream& operator<<(ostream&, PartTimeStudent&);
};

ostream& operator<<(ostream& s, PartTimeStudent& pts) {
	s << "salary = " << pts.salary << ", grade = " << pts.grade << ", " << (Student&)pts << ", " << (Employee&)pts;
	return s;
}

//ostream& operator<<(ostream& s, PartTimeStudent& pts) {
//	s << "salary = " << pts.salary << ", grade = " << pts.grade << ", " << (Student)pts << ", " << (Employee)pts;
//	return s;
//}

int main() {
	Coder* codings[10];
	PartTimeStudent* workStudents[10];
	int select;
	while (true)
	{
		cout << "\n선택 1: Coder 객체 10개 입력과 출력, 2. PartTimeStudent 객체 10개 입력과 출력, 3. 종료" << endl;

		cin >> select;
		switch (select) {
		case 1:  //1: Coder 객체 10개 입력과 출력
			codings[0] = new Coder("cpp", 2, "e1", "math", "LA", "p1", "kim");
			codings[1] = new Coder("java", 3, "e2", "computer", "seoul", "p2", "shin");
			codings[2] = new Coder("python", 4, "e3", "computer", "london", "p3", "park");
			codings[3] = new Coder("c#", 2, "e4", "data analysis", "seoul", "p4", "hong");
			codings[4] = new Coder("c", 6, "e5", "database", "busan", "p5", "woo");
			codings[5] = new Coder("R", 3, "e6", "algorithm", "seoul", "p6", "han");
			codings[6] = new Coder("sql", 2, "e7", "processing", "jeju", "p7", "seo");
			codings[7] = new Coder("java", 4, "e8", "backend", "daegu", "p8", "jeong");
			codings[8] = new Coder("cpp", 10, "e9", "frontend", "busan", "p9", "baek");
			codings[9] = new Coder("python", 3, "e10", "develop", "incheon", "p10", "seong");
			for (int i = 0; i < 1; i++) {
				cout << *codings[i] << endl;
			}
			// 첫번째 for문에서 소멸자를 사용했기 때문에 두번째 for문에서는 nullptr 발생. (객체가 사라졌기 때문에)
			// 소멸자 호출을 안하는 방법으로는 (Person)e 이런 식을 (Person&)e 처럼 참조변수로 만들어서 코드를 작성하면 된다.
			for (int i = 0; i < 1; i++) {
				cout << *codings[i] << endl;
			}
			break;
		case 2://2. PartTimeStudent 객체 10개 입력과 출력
			workStudents[0] = new PartTimeStudent(100, 3, "e12", "s9", "computer", "busan", "p11", "shin");
			workStudents[1] = new PartTimeStudent(200, 4, "e17", "s5", "algorithm", "busan", "p12", "park");
			workStudents[2] = new PartTimeStudent(300, 3, "e12", "s6", "computer", "seoul", "p13", "choi");
			workStudents[3] = new PartTimeStudent(400, 3, "e15", "s10", "data analysis", "incheon", "p14", "hong");
			workStudents[4] = new PartTimeStudent(500, 4, "e16", "s4", "database", "seoul", "p15", "kim");
			workStudents[5] = new PartTimeStudent(600, 4, "e11", "s1", "frontend", "seoul", "p16", "park");
			workStudents[6] = new PartTimeStudent(700, 3, "e17", "s7", "backend", "daegu", "p17", "kim");
			workStudents[7] = new PartTimeStudent(800, 3, "e13", "s3", "design", "daejeon", "p18", "joo");
			workStudents[8] = new PartTimeStudent(900, 3, "e14", "s2", "bigdata", "seoul", "p19", "jang");
			workStudents[9] = new PartTimeStudent(1000, 2, "e12", "s8", "computer", "seoul", "p20", "kim");
			for (int i = 0; i < 10; i++) {
				cout << *workStudents[i];
			}

			for (int i = 0; i < 10; i++) {
				cout << *workStudents[i];
			}
			break;

		default:
			exit(0);
			break;
		}

	}
	system("pause");
	return 1;
}

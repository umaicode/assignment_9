/*
* 객체들의 Set을 포함하는 테이블의 배열을 갖는 클래스 구현하기
*/
// RecordTable은 Set의 Search()를 찾고 Set은 Bag의 search()를 찾게 구현
// RecordSet에서 Add()를 진행했을 때 10개가 넘으면 Add()를 더 못하게 해야한다.
// Bag의 Add(), Delete(), Search(), Print()에서 Bag의 Print()는 virtual로 고쳐야 한다. --> 왜?
// RecordSet의 Print()는 필드가 다른 경우가 존재한다. 
// Bag는 Person객체의 집합 동일한 객체가 있으면 버린다. 
// 각 필드가 다 같은 객체를 동일한 객체라고 한다.
// 중복체크는 이름 가지고 하는 것이 아니라 객체가 같으냐 같지 않냐를 기준으로 한다. 
// Set의 Add()에서 중복체크 해야 한다.

#include <iostream>
#include <string>
#define DefaultSize 50
using namespace std;

class Person { //추상 클래스로 구현한다
private:
	string pid;
	string pname;
public:
	Person() {}
	Person(string pid, string pname) : pid(pid), pname(pname) { }
	virtual void Print() = 0;
	bool equalName(string);
	virtual ~Person() {}

};
bool Person::equalName(string st) {
	if (pname.compare(st) == 0) return true;
	return false;
}
void Person::Print() {
	cout << " **pid = " << pid << ", pname = " << pname;
}
class Employee : public Person {
private:
	string eno;
	string role;
public:
	Employee() :Person() {}
	Employee(string pid, string pname, string eno, string role) : Person(pid, pname), eno(eno), role(role) { }
	void Print();

};

void Employee::Print() {
	Person::Print();
	cout << "eno = " << eno << ", role = " << role;
}
class Coder : public Employee {
private:
	string language;
public:
	Coder() :Employee() {}
	Coder(string pid, string pname, string eno, string role, string language) : Employee(pid, pname, eno, role), language(language) {}
	void Print();
};
void Coder::Print() {
	Employee::Print();
	cout << " language = " << language;
}

class Student : public Person {
private:
	string sid;
	string major;
public:
	Student(string sid, string major, string pid, string pname) : Person(pid, pname), sid(sid), major(major) { }
	void Print();
};
void Student::Print() {
	Person::Print();
	cout << " sid = " << sid << ", major = " << major;
}
class PartTimeStudent : public Student {
private:
	string workType;

public:
	PartTimeStudent(string workType, string sid, string major, string pid, string pname) :
		Student(sid, major, pid, pname), workType(workType) {}
	void Print();
};
void PartTimeStudent::Print() {
	Student::Print();
	cout << " workType = " << workType;;
}


class Bag {
public:
	Bag(int MaxSize = DefaultSize); //생성자
	~Bag(); // 소멸자
	virtual void Add(Person*); // 정수 하나를 bag에 삽입
	virtual Person* Delete(char*); //bag에서 정수 하나를 삭제
	virtual Person* Search(char*);
	bool IsFull();
	// bag이 포화상태이면 true, 그렇지 않으면 false를 반환
	bool IsEmpty();
	// bag이 공백 상태이면 true, 그렇지 않으면 false를 반환
	int Top();
	virtual void Print();
protected:
	void Full(); // bag이 포화상태일 때의 조치
	void Empty(); // bag이 공백 상태일 때의 조치
	Person* arr[DefaultSize];
	int bagMaxSize; // 배열의 크기
	int topBag; // 배열에서 원소가 들어 있는 가장 높은 위치
};
void Bag::Print() {
	for (int i = 0; i < topBag; i++) {
		cout << endl;
		arr[i]->Print();
	}
}
class Set : public Bag {

public:
	Set(int MaxSize = DefaultSize);      //생성자
	~Set();      // 소멸자
	//Set 자료구조에 맞게 Add(), Delete() 함수 재정의
	void Add(Person*);
	Person* Delete(char*);
	void Print();

};

//! ------------------------------- 교수님 코드 ----------------------------------
void Set::Print() {
	for () {
		arr[i].Print();
	}
}
//! ------------------------------- 교수님 코드 ----------------------------------
//! 
class RecordSet : public Set {
	int setMaxSize;
	int topRecordSet;
public:
	Person* Search(char*);
	void Print();
};
class RecordTable {
	int tableMaxSize;
	int topRecordTable; // 마지막 index
	RecordSet* data[];
public:
	void Add(Person*); // 정수 하나를 bag에 삽입
	Person* Delete(char*); //bag에서 정수 하나를 삭제
	Person* Search(char*);
	void Print();
};

//! ------------------------------- 교수님 코드 ----------------------------------
Person* RecordTable::Search(char* str) {
	for () {
		Person* temp;
		temp = data[i].Search(str);
		if (temp != nullptr) {
			return temp;
		}
	}
	return nullptr;
}

void RecordTable::Print() {
	for (int i = 0; i < topRecordTable; i++) {
		data[i]->Print();
	}
}

void RecordTable::Add(Person* p) {
	// data[topRecordTable]에 넣을 수 있는지 없는지 Add()를 하기 전에 체크해야 한다.
	data[topRecordTable]->Add(p); // 몇번째 Set에 Add하라는 의미. 넣기만 하면 안되고 Set에 찼는지 안찼는지 확인해야 한다. (10개가 되었는지 안되었는지)
	if () { topRecordTable++ };
}
//! ------------------------------- 교수님 코드 ----------------------------------

Bag::Bag(int MaxBagSize) : bagMaxSize(MaxBagSize) {
	cout << "Bag::생성자 호출" << endl;
	topBag = 0;

}

Bag::~Bag() {
	cout << "~Bag()호출됨" << endl;
}

bool Bag::IsFull() {
	if (topBag == bagMaxSize - 1)
		return true;
	else
		return false;
}

bool Bag::IsEmpty() {
	if (topBag == 0)
		return true;
	else
		return false;
}

void Bag::Full() {
	cout << "Data structure is full" << endl;
}

void Bag::Empty() {
	cout << "Data structure is empty" << endl;
}

void Bag::Add(Person* x) {
	if (IsFull())
		Full();
	else {
		arr[topBag] = x;
		cout << "BAG에 " << arr[topBag] << "이 추가되었습니다" << endl;
		topBag++;
	}
}

Person* Bag::Delete(char* str) {
	//if (IsEmpty()) {
	 //   Empty();
	   // return x;
	//}
	int deletePos = topBag / 2;
	Person* x = arr[--topBag];
	for (int index = deletePos; index < topBag; index++)
		arr[index] = arr[index + 1];
	//top--;
	return x;
}

int Bag::Top() {
	return topBag;
}

Person* Bag::Search(char* str) {
	int num = topBag;
	for (int i = 0; i < num; i++) {
		if (arr[i]->equalName(str))
			return arr[i];
	}
	return nullptr;
}
Set::Set(int MaxBagSize) : Bag(MaxBagSize) {}

Set::~Set() {
}

void Set::Add(Person* x) {
	arr[topBag] = x;
	topBag++;


	/*
	if (IsFull())
		Full();
	else {
		for (int i = 0; i < MaxSize; i++) {
			if (!(arr[i] == x)) {
				arr[top] = x;
				cout << "SET에 " << arr[top] << "이 추가되었습니다" << endl;
				top++;
				return;
			}
			else {
				cout << "중복된 값 입니다" << endl;
				return;
			}
		}
	}
	*/
}

Person* Set::Delete(char* str) {
	// Set::Search(str)를 호출한다.
	//if (IsEmpty()) {
	 //   Empty();
	 //   return x;
	//}
	//int deletePos = top / 2;
	Person* x = arr[--topBag];
	//for (int index = deletePos; index < top; index++)
	//    arr[index] = arr[index + 1];
	//top--;
	return x;
}

int main() {
	Person* members[30];//Person 선언으로 변경하는 문제 해결 필요 
	RecordTable table;
	//! ------------------------------- 교수님 코드 ----------------------------------
	// Set s;
	//! ------------------------------- 교수님 코드 ----------------------------------
	int select;
	Person* p;

	while (1)
	{
		cout << "\n선택 1: member  객체 30개 입력, 2.table 출력, 3: table 객체 찾기,4. table에서 객체 삭제, 5. members 배열 show 함수, 6. 종료" << endl;
		cin >> select;
		switch (select) {
		case 1://table에 객체 30개 입력
			members[0] = new Coder("p1", "hong", "E1", "Coding", "C++");
			members[1] = new Coder("p2", "hee", "E2", "Coding", "C++");
			members[2] = new Coder("p3", "kim", "E3", "Test", "JAVA");
			members[3] = new Coder("p4", "lee", "E4", "Test", "C#");
			members[4] = new Coder("p5", "ko", "E5", "Design", "GO");
			members[5] = new Coder("p6", "choi", "E6", "Design", "GO");
			members[6] = new Coder("p7", "han", "E7", "Sales", "PYTHON");
			members[7] = new Coder("p8", "na", "E8", "Sales", "C");
			members[8] = new Coder("p9", "you", "E9", "Account", "C++");
			members[9] = new Coder("p10", "song", "E10", "Production", "C#");
			members[10] = new PartTimeStudent("coding", "s001", "computer", "23001", "hong");
			members[11] = new PartTimeStudent("designer", "s002", "DB", "23002", "song");
			members[12] = new PartTimeStudent("tester", "s003", "Java", "23003", "kim");
			members[13] = new PartTimeStudent("manager", "s004", "기계", "13001", "gildong");
			members[14] = new PartTimeStudent("accountant", "s005", "전기", "33001", "gil");
			members[15] = new PartTimeStudent("salesman", "s006", "의류", "43001", "dong");
			members[16] = new PartTimeStudent("planner", "s007", "전자", "53001", "tong");
			members[17] = new PartTimeStudent("audit", "s008", "화공", "63001", "nong");
			members[18] = new PartTimeStudent("DBA", "s009", "화학", "73001", "mong");
			members[19] = new PartTimeStudent("DBA", "s010", "산업", "231", "song");
			members[20] = new PartTimeStudent("coder", "s001", "computer", "201", "hee");
			members[21] = new PartTimeStudent("coder", "s002", "DB", "001", "lee");
			members[22] = new PartTimeStudent("tester", "s003", "Java", "230", "kim");
			members[23] = new PartTimeStudent("designer", "s004", "기계", "231", "choi");
			members[24] = new PartTimeStudent("designer", "s005", "전기", "201", "gam");
			members[25] = new PartTimeStudent("AS", "s006", "의류", "2333", "go");
			members[26] = new PartTimeStudent("coder", "s007", "전자", "2222", "hg");
			members[27] = new PartTimeStudent("audit", "s008", "화공", "23001", "oh");
			members[28] = new PartTimeStudent("engineer", "s009", "화학", "2451", "nice");
			members[29] = new PartTimeStudent("designer", "s010", "산업", "9888", "good");

			for (int i = 0; i < 30; i++)
			{
				table.Add(members[i]);
				//! ------------------------------- 교수님 코드 ----------------------------------
				// s.Add(members[i]);
				//! ------------------------------- 교수님 코드 ----------------------------------
			}
			//! ------------------------------- 교수님 코드 ----------------------------------
			// table.Add(members[0]);
			//! ------------------------------- 교수님 코드 ----------------------------------
			break;
		case 2:
			// table의 모든 객체 출력하기
			//table 모양으로 출력해야 한다: | *** | ???? | === |으로 출력한다.
			table.Print();
		case 3:
			// table에서 객체 찾기

			p = table.Search("kim");
			if (p == nullptr) cout << "kim이 존재하지 않는다" << endl;
			else
				p->Print();
			break;
		case 4:
			//table에서 객체 삭제하기
			p = table.Delete("hong");
			p->Print();

			break;

		default:
			exit(0);

		}
	}
	system("pause");
	return 1;
}
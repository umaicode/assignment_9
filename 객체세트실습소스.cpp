/*
* ��ü���� Set�� �����ϴ� ���̺��� �迭�� ���� Ŭ���� �����ϱ�
*/
// RecordTable�� Set�� Search()�� ã�� Set�� Bag�� search()�� ã�� ����
// RecordSet���� Add()�� �������� �� 10���� ������ Add()�� �� ���ϰ� �ؾ��Ѵ�.
// Bag�� Add(), Delete(), Search(), Print()���� Bag�� Print()�� virtual�� ���ľ� �Ѵ�. --> ��?
// RecordSet�� Print()�� �ʵ尡 �ٸ� ��찡 �����Ѵ�. 
// Bag�� Person��ü�� ���� ������ ��ü�� ������ ������. 
// �� �ʵ尡 �� ���� ��ü�� ������ ��ü��� �Ѵ�.
// �ߺ�üũ�� �̸� ������ �ϴ� ���� �ƴ϶� ��ü�� ������ ���� �ʳĸ� �������� �Ѵ�. 
// Set�� Add()���� �ߺ�üũ �ؾ� �Ѵ�.

#include <iostream>
#include <string>
#define DefaultSize 50
using namespace std;

class Person { //�߻� Ŭ������ �����Ѵ�
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
	Bag(int MaxSize = DefaultSize); //������
	~Bag(); // �Ҹ���
	virtual void Add(Person*); // ���� �ϳ��� bag�� ����
	virtual Person* Delete(char*); //bag���� ���� �ϳ��� ����
	virtual Person* Search(char*);
	bool IsFull();
	// bag�� ��ȭ�����̸� true, �׷��� ������ false�� ��ȯ
	bool IsEmpty();
	// bag�� ���� �����̸� true, �׷��� ������ false�� ��ȯ
	int Top();
	virtual void Print();
protected:
	void Full(); // bag�� ��ȭ������ ���� ��ġ
	void Empty(); // bag�� ���� ������ ���� ��ġ
	Person* arr[DefaultSize];
	int bagMaxSize; // �迭�� ũ��
	int topBag; // �迭���� ���Ұ� ��� �ִ� ���� ���� ��ġ
};
void Bag::Print() {
	for (int i = 0; i < topBag; i++) {
		cout << endl;
		arr[i]->Print();
	}
}
class Set : public Bag {

public:
	Set(int MaxSize = DefaultSize);      //������
	~Set();      // �Ҹ���
	//Set �ڷᱸ���� �°� Add(), Delete() �Լ� ������
	void Add(Person*);
	Person* Delete(char*);
	void Print();

};

//! ------------------------------- ������ �ڵ� ----------------------------------
void Set::Print() {
	for () {
		arr[i].Print();
	}
}
//! ------------------------------- ������ �ڵ� ----------------------------------
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
	int topRecordTable; // ������ index
	RecordSet* data[];
public:
	void Add(Person*); // ���� �ϳ��� bag�� ����
	Person* Delete(char*); //bag���� ���� �ϳ��� ����
	Person* Search(char*);
	void Print();
};

//! ------------------------------- ������ �ڵ� ----------------------------------
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
	// data[topRecordTable]�� ���� �� �ִ��� ������ Add()�� �ϱ� ���� üũ�ؾ� �Ѵ�.
	data[topRecordTable]->Add(p); // ���° Set�� Add�϶�� �ǹ�. �ֱ⸸ �ϸ� �ȵǰ� Set�� á���� ��á���� Ȯ���ؾ� �Ѵ�. (10���� �Ǿ����� �ȵǾ�����)
	if () { topRecordTable++ };
}
//! ------------------------------- ������ �ڵ� ----------------------------------

Bag::Bag(int MaxBagSize) : bagMaxSize(MaxBagSize) {
	cout << "Bag::������ ȣ��" << endl;
	topBag = 0;

}

Bag::~Bag() {
	cout << "~Bag()ȣ���" << endl;
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
		cout << "BAG�� " << arr[topBag] << "�� �߰��Ǿ����ϴ�" << endl;
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
				cout << "SET�� " << arr[top] << "�� �߰��Ǿ����ϴ�" << endl;
				top++;
				return;
			}
			else {
				cout << "�ߺ��� �� �Դϴ�" << endl;
				return;
			}
		}
	}
	*/
}

Person* Set::Delete(char* str) {
	// Set::Search(str)�� ȣ���Ѵ�.
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
	Person* members[30];//Person �������� �����ϴ� ���� �ذ� �ʿ� 
	RecordTable table;
	//! ------------------------------- ������ �ڵ� ----------------------------------
	// Set s;
	//! ------------------------------- ������ �ڵ� ----------------------------------
	int select;
	Person* p;

	while (1)
	{
		cout << "\n���� 1: member  ��ü 30�� �Է�, 2.table ���, 3: table ��ü ã��,4. table���� ��ü ����, 5. members �迭 show �Լ�, 6. ����" << endl;
		cin >> select;
		switch (select) {
		case 1://table�� ��ü 30�� �Է�
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
			members[13] = new PartTimeStudent("manager", "s004", "���", "13001", "gildong");
			members[14] = new PartTimeStudent("accountant", "s005", "����", "33001", "gil");
			members[15] = new PartTimeStudent("salesman", "s006", "�Ƿ�", "43001", "dong");
			members[16] = new PartTimeStudent("planner", "s007", "����", "53001", "tong");
			members[17] = new PartTimeStudent("audit", "s008", "ȭ��", "63001", "nong");
			members[18] = new PartTimeStudent("DBA", "s009", "ȭ��", "73001", "mong");
			members[19] = new PartTimeStudent("DBA", "s010", "���", "231", "song");
			members[20] = new PartTimeStudent("coder", "s001", "computer", "201", "hee");
			members[21] = new PartTimeStudent("coder", "s002", "DB", "001", "lee");
			members[22] = new PartTimeStudent("tester", "s003", "Java", "230", "kim");
			members[23] = new PartTimeStudent("designer", "s004", "���", "231", "choi");
			members[24] = new PartTimeStudent("designer", "s005", "����", "201", "gam");
			members[25] = new PartTimeStudent("AS", "s006", "�Ƿ�", "2333", "go");
			members[26] = new PartTimeStudent("coder", "s007", "����", "2222", "hg");
			members[27] = new PartTimeStudent("audit", "s008", "ȭ��", "23001", "oh");
			members[28] = new PartTimeStudent("engineer", "s009", "ȭ��", "2451", "nice");
			members[29] = new PartTimeStudent("designer", "s010", "���", "9888", "good");

			for (int i = 0; i < 30; i++)
			{
				table.Add(members[i]);
				//! ------------------------------- ������ �ڵ� ----------------------------------
				// s.Add(members[i]);
				//! ------------------------------- ������ �ڵ� ----------------------------------
			}
			//! ------------------------------- ������ �ڵ� ----------------------------------
			// table.Add(members[0]);
			//! ------------------------------- ������ �ڵ� ----------------------------------
			break;
		case 2:
			// table�� ��� ��ü ����ϱ�
			//table ������� ����ؾ� �Ѵ�: | *** | ???? | === |���� ����Ѵ�.
			table.Print();
		case 3:
			// table���� ��ü ã��

			p = table.Search("kim");
			if (p == nullptr) cout << "kim�� �������� �ʴ´�" << endl;
			else
				p->Print();
			break;
		case 4:
			//table���� ��ü �����ϱ�
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
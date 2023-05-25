/*
* 객체들의 Set을 포함하는 테이블의 배열을 갖는 클래스 구현하기
*/
// Person 클래스는 추상클래스로 구현하여야 한다.
// 컨테이너 클래스를 사용해서 테이블을 만드는 것!
// main에서 거꾸로 찾아가면서 만들어 나가는 것이 객체지향 프로그래밍 구현하는데 수월해짐. (뉴비 버전)
#include <iostream>
#include <string>
#define DefaultSize 50
using namespace std;

class Employee;
class Person { //추상 클래스로 구현한다
protected:
	string pid;
	string pname;
public:
	string GetName() { return pname; }
	void SetName(char* str) { pname = str; } // 수정 필요 // 아예삭제되는 것이 아니라 *******로 출력되게끔 수정 필요



	Person() {}
	Person(string pid, string pname) : pid(pid), pname(pname) { }
	virtual void Print() = 0; // pure virtual로 구현
	virtual bool Equals(Employee*) = 0; // pure virtual로 구현 // 수정 필요.
	virtual ~Person() {}

};

void Person::Print() {
	cout << pid << ", " << pname << ", ";
}

class Employee : public Person {
private:
	string eno;
	string role;
public:
	Employee() :Person() {}
	Employee(string pid, string pname, string eno, string role) : Person(pid, pname), eno(eno), role(role) { }
	virtual void Print();
	virtual bool Equals(Employee* p);
};

void Employee::Print() {
	Person::Print();
	cout << eno << ", " << role;
}

bool Employee::Equals(Employee* p) {
	return pid == p->pid && pname == p->pname && eno == p->eno && role == p->role;
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
	cout << ", " << language;
}


class Student : public Employee {
private:
	string sid;
	string major;
public:
	Student(string sid, string major, string eno, string role, string pid, string pname) : Employee(pid, pname, eno, role), sid(sid), major(major) { }
	void Print();
};

void Student::Print() {
	Employee::Print();
	cout << ", " << sid << ", " << major;
}

class Bag {
public:
	virtual int Add(Employee*); // 정수 하나를 bag에 삽입
	virtual int Delete(char*); //bag에서 정수 하나를 삭제
	virtual Employee* Search(char*);
	bool IsFull();
	// bag이 포화상태이면 true, 그렇지 않으면 false를 반환
	bool IsEmpty();
	// bag이 공백 상태이면 true, 그렇지 않으면 false를 반환
	int Top();
	virtual void Print();

protected:
	// Bag(int bagSize); // bag 생성자를 protected로함 -> main에서 호출할 수 없게.

	// ----------------------- 교수님 코드 -------------------------------
	Bag(int bagSize) {
		arr = new Employee * [bagSize];
		bagMaxSize = bagSize;
		topBag = 0;
		for (int i = 0; i < bagSize; i++) {
			arr[i] = nullptr;
		}
		// main에서 객체를 만들었는데 여기서 for loop를 돌려서 객체를 또 만들면 runtime-error 발생. 빈 객체 만들어서 넣어버리면 Add 작동안한다.
		//for () {
		//	arr[i] = new Employee(); 
		//}
	}
	// ----------------------- 교수님 코드 -------------------------------

	void Full(); // bag이 포화상태일 때의 조치
	void Empty(); // bag이 공백 상태일 때의 조치

	Employee** arr; //> 생성자에서 arr = new Employee*[Size]; > arr[i] = new Employee();
	int bagMaxSize; // 배열의 크기
	int topBag; // 배열에서 원소가 들어 있는 가장 높은 위치
	//*
	~Bag() {
		for (int i = 0; i < bagMaxSize; i++) {
			delete arr[i];
		}
		delete[] arr;
	}
	// */
};

Employee* Bag::Search(char* str) {
	for (int i = 0; i < topBag; i++) {
		if (strcmp(arr[i]->GetName().c_str(), str) == 0) {
			return arr[i];
		}
	}
	return nullptr;
}

void Bag::Print() {
	Employee* p;
	for (int i = 0; i < topBag; i++) {
		p = arr[i];
		p->Print();
		cout << " | ";
	}
}

int Bag::Add(Employee* p) {
	if (IsFull()) {
		Full();
		return -1;
	}

	if (topBag < bagMaxSize) {
		arr[topBag++] = p;
		return 1;
	}

	return -1;
}

//int Bag::Delete(char* str) {
//	if (IsEmpty()) {
//		Empty();
//		return -1;
//	}
//
//	for (int i = 0; i < topBag; i++) {
//		if (strcmp(arr[i]->GetName().c_str(), str) == 0) {
//			arr[i]->SetName("*******");
//			return 0;
//		}
//	}
//
//	return -1;
//}

int Bag::Delete(char* str) {
	for (int i = 0; i < topBag; i++) {
		if (arr[i]->GetName() == str) {
			arr[i]->SetName("*******");
			return 1;
		}
	}
	return 0;
}


bool Bag::IsFull() {
	if (topBag == bagMaxSize) {
		return true;
	}
	else {
		return false;
	}
}

bool Bag::IsEmpty() {
	if (topBag == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Bag::Full() {
	cout << "Data Structure is FULL!!!" << endl;
}

void Bag::Empty() {
	cout << "Data Structure is EMPTY!!!" << endl;
}

class Set : public Bag {
public:
	Set(int setSize) :Bag(setSize) {} // Set의 생성자만 main에서 호출할 수 있게 public 선언.
	int Add(Employee*); // Bag의 Add()를 virtual로 지정 ->
	int Delete(char*);
	void Print();
	Employee* Search(char*);
};

int Set::Add(Employee* p) {
	if (IsFull()) {
		Full();
		return -1;
	}
	else {
		for (int i = 0; i < topBag; i++) {
			if ((*(arr[i])).Equals(p)) {
				cout << "중복된 값입니다." << endl;
				return -1;
			}
		}
		Bag::Add(p);
		return 0;
	}
}

int Set::Delete(char* str) {
	return Bag::Delete(str);
}

void Set::Print() {
	for (int i = 0; i < topBag; i++) {
		arr[i]->Print();
		if (i < topBag - 1) {
			cout << " | ";
		}
	}
	if (topBag > 0 && topBag % 5 != 0) {
		cout << " | ";
	}
}

Employee* Set::Search(char* str) {
	return Bag::Search(str);
}

class RecordSet : public Set {
	int setMaxSize;//5개의 레코드 수
	int topRecordSet;//해당 레코드세트에서 입력할 위치
public:
	RecordSet(int maxSize) :Set(maxSize), setMaxSize(maxSize) {
		topRecordSet = 0;
	}
	Employee* Search(char*);
	void Print();
	int Add(Employee* p);
};

// 5개 이상이면 top을 증가시켜서 다음 행으로 보내야 한다.
// 첫번째 행 포인터 역할을 하는 것이 topRecordTable 변수이다.
// 즉 5개가 다 차면 ++가 되어야 한다.
// 포인터의 위치는 Bag의 topBag 변수가 각 행의 열 증가.
// keypoint는 topRecordTable과 topBag 를 사용하여 행렬을 이용하는 것.

int RecordSet::Add(Employee* p) {
	if (topRecordSet < setMaxSize) {
		if (Set::Add(p) != -1) {
			topRecordSet++;
			if (topRecordSet == setMaxSize) {
				cout << "가득 찼습니다." << endl;
				return 1; // 행이 증가함을 알리기 위해 1을 반환
			}
			return 0;
		}
	}

	if (topRecordSet + 1 < setMaxSize) {
		topRecordSet++;
		Set::Add(p);
		return 0;
	}

	return -1; // 모든 열이 가득 찬 경우
}

Employee* RecordSet::Search(char* name) {
	return Set::Search(name);
}

void RecordSet::Print() {
	Set::Print();
	if (topRecordSet > 0 && topRecordSet % 5 != 0) {
		cout << " | ";
	}
}

class RecordTable {
	int tableMaxSize;
	int topRecordTable;
	RecordSet** data; // 첫번째 포인터는 배열을 가리키고 두번째 포인터는 recordSet을 가리키게 된다.
	int capacity;
public:
	RecordTable(int numberSet, int numberRecords) :tableMaxSize(numberSet), capacity(numberRecords) {
		topRecordTable = 0; // 첫번째 줄
		data = new RecordSet * [numberSet]; //10개의 set
		for (int i = 0; i < numberSet; i++) {
			data[i] = new RecordSet(numberRecords);//각 set는 5개 records
		}
	}
	int Add(Employee*); // 정수 하나를 bag에 삽입
	int Delete(char*);
	Employee* Search(char*);
	void Print();
};

// ----------------------- 교수님 코드 -------------------------------
//int RecordTable::Add(Employee* e) {
//	// 0 을 i로 바꾸고 i는 top을 통해 움직이게 만들기.
//	for (int i = 0; i < tableMaxSize; i++) {
//		if (data[i]->IsFull()) {
//			continue;
//		}
//		data[i]->Add(e);
//		return 0;
//	}
//	return -1;
//}
// ----------------------- 교수님 코드 -------------------------------

int RecordTable::Add(Employee* e) {
	int result = data[topRecordTable]->Add(e); // RecordSet의 Add() 메소드 호출 결과 저장
	if (result == 1) { // 행이 증가했을 경우
		topRecordTable++; // topRecordTable 변수를 증가시킴
		if (topRecordTable == tableMaxSize) {
			cout << "테이블이 가득 찼습니다." << endl;
			return 1; // 테이블이 가득 찼음을 알리기 위해 1을 반환
		}
	}
	return 0;
}

void RecordTable::Print() {
	for (int i = 0; i < topRecordTable; i++) {
		data[i]->Print();
		if (i < topRecordTable) {
			cout << " | " << endl;
		}
	}
}


int RecordTable::Delete(char* str) {
	int deletedCount = 0;

	for (int i = 0; i < tableMaxSize; i++) {
		if (data[i]->Delete(str) == 1) {
			deletedCount++;
		}
	}
	return deletedCount;
}


Employee* RecordTable::Search(char* str) {
	for (int i = 0; i < tableMaxSize; i++) {
		Employee* result = data[i]->Search(str);
		if (result != nullptr) {
			return result; // 레코드를 성공적으로 찾은 경우
		}
	}
	return nullptr; // 찾을 레코드가 없는 경우
}


int main() {
	Employee* members[30];//Employee 선언으로 변경하는 문제 해결 필요 
	RecordTable table(10, 5);//10개의 record sets, 각 set은 5개의 records, 10 => Set개수, 5 => 1개의 Set에 포함된 Records
	int select;
	Employee* p;
	int result;
	while (1)
	{
		cout << "\n선택 1: member  객체 30개 입력, 2.table 출력, 3: table 객체 찾기,4. table에서 객체 삭제, 5. 종료" << endl;
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
			members[10] = new Student("s011", "coding", "E33", "manager", "23001", "hong");
			members[11] = new Student("s012", "coding", "E33", "manager", "23002", "ong");
			members[12] = new Student("s013", "coding", "E33", "manager", "23003", "dong");
			members[13] = new Student("s014", "coding", "E33", "manager", "23004", "fong");
			members[14] = new Student("s015", "coding", "E33", "manager", "23011", "tong");
			members[15] = new Student("s016", "coding", "E33", "manager", "23021", "nong");
			members[16] = new Student("s017", "coding", "E33", "manager", "23031", "mong");
			members[17] = new Student("s018", "coding", "E33", "manager", "23041", "kong");
			members[18] = new Student("s019", "coding", "E33", "manager", "23051", "long");
			members[19] = new Student("s020", "coding", "E33", "manager", "23101", "pong");
			members[20] = new Student("s021", "coding", "E53", "manager", "23141", "lim");
			members[21] = new Student("s022", "coding", "E53", "manager", "23241", "mim");
			members[22] = new Student("s023", "coding", "E53", "manager", "23341", "bim");
			members[23] = new Student("s024", "coding", "E53", "manager", "23441", "dim");
			members[24] = new Student("s025", "coding", "E53", "manager", "23541", "rim");
			members[25] = new Student("s026", "coding", "E53", "manager", "23641", "qim");
			members[26] = new Student("s021", "coding", "E53", "manager", "23741", "fim");
			members[27] = new Student("s021", "coding", "E53", "manager", "23841", "him");
			members[28] = new Student("s027", "coding", "E53", "manager", "23941", "jim");
			members[29] = new Student("s027", "coding", "E53", "manager", "24041", "jjj");


			for (int i = 0; i < 30; i++)
			{
				table.Add(members[i]);

			}
			break;
		case 2:
			// table의 모든 객체 출력하기
			//table 모양으로 출력해야 한다: | *** | ???? | === |으로 출력한다.

			table.Print();
			break;
		case 3:
			// table에서 객체 찾기

			p = table.Search("kim"); // 문자열이 계속 전달되서 person객체와 비교
			if (p == nullptr) cout << "kim이 존재하지 않는다" << endl;
			else
				p->Print();
			break;
		case 4:
			//table에서 객체 삭제하기
			result = table.Delete("hong"); // 이름을 삭제하는 것이 아니라 특수문자로 바꾸어야 함.
			if (result > 0) {
				cout << "삭제된 records 숫자 " << result << endl;
			}

			break;

		default:
			exit(0);

		}
	}
	system("pause");
	return 1;
}
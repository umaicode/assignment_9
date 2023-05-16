/*
* ��ü���� Set�� �����ϴ� ���̺��� �迭�� ���� Ŭ���� �����ϱ�
*/
// Person Ŭ������ �߻�Ŭ������ �����Ͽ��� �Ѵ�.
// �����̳� Ŭ������ ����ؼ� ���̺��� ����� ��!
// main���� �Ųٷ� ã�ư��鼭 ����� ������ ���� ��ü���� ���α׷��� �����ϴµ� ��������. (���� ����)
#include <iostream>
#include <string>
#define DefaultSize 50
using namespace std;
class Employee;
class Person { //�߻� Ŭ������ �����Ѵ�
public:
	string GetName() { return pname; }
	void SetName(char* str) { pname = str; }
	string pid;
	string pname;
	Person() {}
	Person(string pid, string pname) : pid(pid), pname(pname) { }
	virtual void Print() = 0; // pure virtual�� ����
	virtual bool Equals(Employee*) = 0; // pure virtual�� ����
	virtual ~Person() {}

};

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

class Coder : public Employee {
private:
	string language;
public:
	Coder() :Employee() {}
	Coder(string pid, string pname, string eno, string role, string language) : Employee(pid, pname, eno, role), language(language) {}
	void Print();
};


class Student : public Employee {
private:
	string sid;
	string major;
public:
	Student(string sid, string major, string eno, string role, string pid, string pname) : Employee(pid, pname, eno, role), sid(sid), major(major) { }
	void Print();
};



class Bag {
public:
	virtual int Add(Employee*); // ���� �ϳ��� bag�� ����
	virtual int Delete(char*); //bag���� ���� �ϳ��� ����
	virtual Employee* Search(char*);
	bool IsFull();
	// bag�� ��ȭ�����̸� true, �׷��� ������ false�� ��ȯ
	bool IsEmpty();
	// bag�� ���� �����̸� true, �׷��� ������ false�� ��ȯ
	int Top();
	virtual void Print();

protected:
	Bag(int bagSize); // bag �����ڸ� protected���� -> main���� ȣ���� �� ����.

	// ----------------------- ������ �ڵ� -------------------------------
	Bag(int bagSize) {
		arr = new Employee * [bagSize];
		// main���� ��ü�� ������µ� ���⼭ for loop�� ������ ��ü�� �� ����� runtime-error �߻�. �� ��ü ���� �־������ Add �۵����Ѵ�.
		//for () {
		//	arr[i] = new Employee(); 
		//}
	}
	// ----------------------- ������ �ڵ� -------------------------------

	void Full(); // bag�� ��ȭ������ ���� ��ġ
	void Empty(); // bag�� ���� ������ ���� ��ġ

	Employee** arr; //> �����ڿ��� arr = new Employee*[Size]; > arr[i] = new Employee();
	int bagMaxSize; // �迭�� ũ��
	int topBag; // �迭���� ���Ұ� ��� �ִ� ���� ���� ��ġ
	//*
	~Bag() {
		for (int i = 0; i < bagMaxSize; i++) {
			delete arr[i];
		}
		delete[] arr;
	}
	// */
};


class Set : public Bag {
public:
	Set(int setSize) :Bag(setSize) {} // Set�� �����ڸ� main���� ȣ���� �� �ְ� public ����.
	int Add(Employee*); // Bag�� Add()�� virtual�� ���� ->
	int Delete(char*);
	void Print();
	Employee* Search(char*);
};


class RecordSet : public Set {
	int setMaxSize;//5���� ���ڵ� ��
	int topRecordSet;//�ش� ���ڵ弼Ʈ���� �Է��� ��ġ
public:
	RecordSet(int maxSize) :Set(maxSize), setMaxSize(maxSize) {
		topRecordSet = 0;
	}
	Employee* Search(char*);
	void Print();
	int Add(Employee* p);
};

int RecordSet::Add(Employee* p) {
	if () {
		Set::Add(p);
	}
}


class RecordTable {
	int tableMaxSize;
	int topRecordTable;
	RecordSet** data; // ù��° �����ʹ� �迭�� ����Ű�� �ι�° �����ʹ� recordSet�� ����Ű�� �ȴ�.
	int capacity;
public:
	RecordTable(int numberSet, int numberRecords) :tableMaxSize(numberSet), capacity(numberRecords) {
		topRecordTable = 0; // ù��° ��
		data = new RecordSet * [numberSet]; //10���� set
		for (int i = 0; i < numberSet; i++) {
			data[i] = new RecordSet(numberRecords);//�� set�� 5�� records
		}
	}
	int Add(Employee*); // ���� �ϳ��� bag�� ����
	int Delete(char*);
	Employee* Search(char*);
	void Print();
};

// ----------------------- ������ �ڵ� -------------------------------
int RecordTable::Add(Employee* e) {
	// 0 �� i�� �ٲٰ� i�� top�� ���� �����̰� �����.
	for () {
		data[i]->Add(e);
	}
}
// ----------------------- ������ �ڵ� -------------------------------

int main() {
	Employee* members[30];//Employee �������� �����ϴ� ���� �ذ� �ʿ� 
	RecordTable table(10, 5);//10���� record sets, �� set�� 5���� records, 10 => Set����, 5 => 1���� Set�� ���Ե� Records
	int select;
	Employee* p;
	int result;
	while (1)
	{
		cout << "\n���� 1: member  ��ü 30�� �Է�, 2.table ���, 3: table ��ü ã��,4. table���� ��ü ����, 5. ����" << endl;
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
			// table�� ��� ��ü ����ϱ�
			//table ������� ����ؾ� �Ѵ�: | *** | ???? | === |���� ����Ѵ�.

			table.Print();
			break;
		case 3:
			// table���� ��ü ã��

			p = table.Search("kim");
			if (p == nullptr) cout << "kim�� �������� �ʴ´�" << endl;
			else
				p->Print();
			break;
		case 4:
			//table���� ��ü �����ϱ�
			result = table.Delete("hong");
			if (result > 0)
				cout << "������ records ����" << result << endl;

			break;

		default:
			exit(0);

		}
	}
	system("pause");
	return 1;
}
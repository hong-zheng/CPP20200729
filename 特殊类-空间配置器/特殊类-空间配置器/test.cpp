#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <mutex>
#include <vector>
#include <typeinfo>
using namespace std;



int func() { return 0; }
void testDecltype(){

	decltype(func()) i;
	cout << sizeof(i) << endl;

	const int x = 0;
	decltype(x) y = 1;
	decltype(x + y) z = 10;
	cout << sizeof(z) << endl;
	cout << typeid(z).name() << endl;

	/*
		decltype���Ƶ�����
		decltype(exp)
			exp�Ǳ��ʽ���������ͺ�exp������ͬ
			exp�Ǻ�������ʱ��decltype(exp)�ͺ�������ֵ������ͬ
			�����������exp����ֵ��decltype(exp)��exp���͵���ֵ���͵�����
	*/

}

void t2(){
	int a = 0;
	int b = 0;
	decltype(a + b) c = 0; // c��int����Ϊ(a+b)����һ����ֵ
	decltype(a += b) d = c; // d��int&����Ϊ(a+b)����һ����ֵ

	d = 20;
	cout << c << endl; //20
}

/*
	auto��decltype�����ʹ�ã�
	һ�����ʹ�����Ƶ���������ֵ���������ϣ�
	���ڣ�
	����t��u�����Ͳ�ȷ�����޷��Ƶ���return_type�ľ�������
	template<typename T,typename U>
	return_type add(T t,U u)
	{
		return t+u ;
	}
	��return_typeΪdecltype(t+u)Ҳ�����У���Ϊt��u��δ����
*/
// �������ͺ��õ����ʹ�÷���
template<typename T,typename U>
auto add(T t, U u)->decltype(t + u)
{
	return t + u;
}

void testAuto()
{
	int a = 10;
	float b = 10.0f;
	auto c = add(a, b);

	cout << c << endl;

	/*
		auto��ʹ�ñ������ϳ�ʼ���������޷��Ƶ�������
		auto��һ�ж���������ʱ�������������Ƶ����ܲ��������ԣ��������ʧ��

	*/

	//��ǰ�б���ʧ�ܣ�fΪfloat���ͣ�gΪint����
	//auto f = 0.1f, g = 10;

	// auto������Ϊ��������
	//������auto������Ϊ�Ǿ�̬��Ա����
	//auto���ܶ������飬���Զ���ָ��
	//auto�޷��Ƶ���ģ�����

	vector<int> ret;
	cout << &ret << endl;
	vector<int>  ret1 = ret;
	cout << &ret1 << endl;

}
/*
*/
int main1(){
	//testDecltype();
	testAuto();

	system("pause");
	return 0;
}


//
//
//
//// ���һ����ֻ���ڶ��ϴ�����ʽ
//// ֻ���ڶ��ϴ����������
//// 1�����캯��˽��
//// 2���ṩһ����̬�Ķ��ϴ�������ķ���
//// 3����������������������Ϊ˽�У��Ҳ�ʵ�֣���������Ϊdelete����
////class HeapOnly{
////
////public:
////	// �ṩһ���ڶ���ִ�еĺ���
////	// ָ��һ�㶼���ڶ��ϴ�������
////	static HeapOnly* getInstance(){
////		// ���ϴ�������
////		return new HeapOnly;
////	}
////private:
////
////	// �����е�����˽��
////	HeapOnly() 
////	{}
////
////	// ֻ������ʵ��
////	HeapOnly(const HeapOnly& ho);
////	// ��������Ҳ����
////	//HeapOnly(const HeapOnly& ho)=delete;
////};
////void test1(){
////	//HeapOnly ho; //��ջ�ϴ�������
////	//HeapOnly ho; //���ò���
////
////	HeapOnly* ptr = HeapOnly::getInstance();
////
////	//��������:��ֹ��������
////	//HeapOnly copy(*ptr);
////}
////
////// ֻ����ջ�ϴ����������
////// 1�����캯��˽��
////// 2���ṩһ�����еľ�̬��ջ�ϵĴ�������ķ���
////class StackOnly{
////public:
////	static StackOnly getInstance()
////	{
////		return StackOnly();
////	}
////private:
////	StackOnly(){}
////};
////
////void test2(){
////	StackOnly so = StackOnly::getInstance();
////}
//
//// ֻ����ջ�ϴ����������
//// 1�����캯��˽��
//// 2���ṩһ�����еľ�̬��ջ�ϴ�������ķ���
//// 3����operator new ��������Ϊdelete����
////class StackOnly2{
////public:
////	static StackOnly2 getInstance()
////	{
////		return StackOnly2();
////	}
////	void* operator new(size_t n) = delete;
////private:
////	StackOnly2(){};
////};
////
////// ��ֹ��������
////// ��������͸�ֵ���������Ϊdelete��������������Ϊ˽�е�
////// �Ҳ�ʵ��
////class NoCopy{
////public:
////	NoCopy(){};
////private:
////	NoCopy(const NoCopy& nc);
////	//NoCopy(const NoCopy& nc)=delete;
////
////	//NoCopy& operator = (const NoCopy& nc);
////	NoCopy& operator = (const NoCopy& nc) = delete;
////};
////
//////���ܱ��̳е���
////// ����Ĺ�������Ϊ˽�У����ܱ��̳�
////class NoH{
////private: // ���캯������Ϊ˽�еģ��޷���
////	NoH(){};
////};
////
////// ���ܱ��̳е��ࣺ����Ϊfinal��
////// ����������ඨ��Ϊfinal��
////class NoH2 final{
////
////};
////
////// ����ģʽ
////// ���ģʽ:����ģʽ
////// ����ģʽ
////// 1�����캯��˽��
////// 2���ṩһ����̬�ķ������ص���
////// 3������һ����̬�ĵ�����Ա
////// 4����������͸�ֵ����Ϊdelete����
////
////// �ص㣺ʵ�ּ򵥣����߳�Ч�ʸ�
////// ȱ�㣺��������������������������ʼ����˳���޷�����˳��
////
////class singleton{
////public:
////	static singleton* getInstance()
////	{
////		//����һ�����ڵĶ���
////		//��һ����̬�Ķ��������������ʹ����ɹ�
////		return &_single;
////	}
////private:
////	//���췽��˽��
////	singleton(){};
////
////	// ��ǰ��Ա�����Ǿ�̬�ģ��Ǿ�̬������
////
////	//�����ڶ��󣬲������ݴ�С
////	// �������ʼ��
////	static singleton _single;
////
////	//��ֹ�����Ĳ���
////	singleton(const singleton& slg) = delete;
////	singleton& operator=(const singleton& slg) = delete;
////
////};
////// ��̬��Ա�ĳ�ʼ��
////singleton singleton::_single;
////
////
////
////// ����ģʽ��������֢
//////���캯����Ȼ��Ҫ˽�л�
////// ��֤�̰߳�ȫ���޸�ָ�룩��˫������Ч��
////
////// �ص㣺�ӳټ��أ����������죬����ָ�������������ĳ�ʼ��˳��
////// ʵ�ָ��ӣ���Ҫ���Ƕ��߳�����
////class Singleton2{
////public:
////	static Singleton2* getInstance(){
////		// ˫��飺
////		// ˫��飺ʱ����٣�û����ô����������ʱ�����ʵĸı�
////		if (_ptr == nullptr){
////			// ������Ŀ�ľ��Ǳ�ֻ֤������һ�������������Ƕ��
////			_mtx.lock();
////			//��Ҫ�õ�����ͬһ������
////			if (_ptr == nullptr){
////				// ��һ�ε��ô�������
////				// �˴���д�ж��̵߳��³�������
////
////				// ����������ͬʱ���˴�
////				// һ�����̴�������ֵ��_ptr֮�󣬻�û���ͷ�
////				// �ڶ�������������������ֵ
////				// �����Ҫ��֤�Ǵ��в���
////				_ptr = new Singleton2;
////			}
////			_mtx.unlock();
////		}
////		return _ptr;
////	}
////
////	// ����Դ
////	// ��д�ɲ�д
////	class GC
////	{
////		~GC()
////		{
////			if (_ptr)
////			{
////				delete _ptr;
////			}
////		}
////	};
////private:
////	Singleton2(){};
////	//������
////	Singleton2(const Singleton2&) = delete;
////	Singleton2& operator=(const Singleton2&) = delete;
////	static Singleton2* _ptr;
////	// ��̬�ͳ������������һ��
////	static mutex _mtx;
////
////	static GC _gc;
////};
////
////mutex Singleton2::_mtx;
////
////Singleton2* Singleton2::_ptr = nullptr;
////
////Singleton2::GC Singleton2::_gc;
//
//class A{
//public:
//	virtual void fun()
//	{
//
//	}
//};
//
//class B :public A{
//private:
//	int _b = 0;
//};
//// ����ת��
//
//void testast(){
//	// ��ʽ����ת��
//	char c = 'a';
//	int a = c;
//	float f = 1.2f;
//	int d = (int)f;
//
//	//ǿ��ת��:���Ͳ��Ƚϴ�
//	int* ptr = &a;
//	int e = (int)ptr;
//	int * ptr2 = (int*)a;
//
//	//C++����ǿת����
//	// static_cast
//	// reinterpret_cast
//	// const_cast
//	// dynamic_cast
//
//	// static_cast��֧��������ʽ����ת��
//	int m = static_cast<int>(c);
//	int d2 = static_cast<int>(f);
//	// static_cast��֧��ǿ������ת��
//	//int* ptr3 = static_cast<int*>(a);
//	int* ptr3 = reinterpret_cast<int*>(a);
//
//	//����ָ���뺯��֮�䲻ƥ��Ҳ������ reinterpret_cast ǿת
//
//	// const_cast��ȥ��const����
//	const int ca = 10;
//	const int* ptrca = &ca;
//
//	int* ptrca1 = const_cast<int*>(&ca);
//
//	//dynamic_cast��ֻ�����ڶ�̬����������ת��
//	// ���а�ȫת�������ת�����ɹ������ؿ�ָ��
//
//	A* pa = new A;
//	A* pb = new B;
//
//	B* pb2 = (B*)pa;
//
//	//static_cast������ת���࣬�����а�ȫ�ж�
//	B* pb5 = static_cast<B*>(pa);
//
//	B* pb3 = dynamic_cast<B*>(pa);
//	B* pb4 = dynamic_cast<B*>(pb);
//
//}
//void test(){
//
//}


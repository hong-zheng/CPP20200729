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
		decltype的推导规则：
		decltype(exp)
			exp是表达式，其结果类型和exp类型相同
			exp是函数调用时，decltype(exp)和函数返回值类型相同
			其他情况：若exp是左值，decltype(exp)是exp类型的左值类型的引用
	*/

}

void t2(){
	int a = 0;
	int b = 0;
	decltype(a + b) c = 0; // c是int，因为(a+b)返回一个右值
	decltype(a += b) d = c; // d是int&，因为(a+b)返回一个左值

	d = 20;
	cout << c << endl; //20
}

/*
	auto和decltype的配合使用；
	一般配合使用在推导函数返回值类型问题上：
	对于：
	其中t和u的类型不确定，无法推导出return_type的具体类型
	template<typename T,typename U>
	return_type add(T t,U u)
	{
		return t+u ;
	}
	当return_type为decltype(t+u)也不可行，因为t和u尚未定义
*/
// 返回类型后置的配合使用方法
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
		auto的使用必须马上初始化，否则无法推导出类型
		auto在一行定义多个变量时，各个变量的推导不能产生二义性，否则编译失败

	*/

	//当前行编译失败：f为float类型，g为int类型
	//auto f = 0.1f, g = 10;

	// auto不能作为函数参数
	//在类中auto不能作为非静态成员变量
	//auto不能定义数组，可以定义指针
	//auto无法推导出模板参数

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
//// 设计一个类只能在堆上创建方式
//// 只能在堆上创建对象的类
//// 1、构造函数私有
//// 2、提供一个静态的堆上创建对象的方法
//// 3、防拷贝：拷贝构造声明为私有，且不实现，或者声明为delete函数
////class HeapOnly{
////
////public:
////	// 提供一个在堆上执行的函数
////	// 指针一般都是在堆上创建对象
////	static HeapOnly* getInstance(){
////		// 堆上创建对象
////		return new HeapOnly;
////	}
////private:
////
////	// 必须有但是是私有
////	HeapOnly() 
////	{}
////
////	// 只声明不实现
////	HeapOnly(const HeapOnly& ho);
////	// 或者这样也可以
////	//HeapOnly(const HeapOnly& ho)=delete;
////};
////void test1(){
////	//HeapOnly ho; //在栈上创建对象
////	//HeapOnly ho; //调用不可
////
////	HeapOnly* ptr = HeapOnly::getInstance();
////
////	//拷贝构造:禁止拷贝构造
////	//HeapOnly copy(*ptr);
////}
////
////// 只能在栈上创建对象的类
////// 1、构造函数私有
////// 2、提供一个公有的静态的栈上的创建对象的方法
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
//// 只能在栈上创建对象的类
//// 1、构造函数私有
//// 2、提供一个公有的静态的栈上创建对象的方法
//// 3、把operator new 函数声明为delete函数
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
////// 禁止拷贝的类
////// 拷贝构造和赋值运算符声明为delete函数，或者声明为私有的
////// 且不实现
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
//////不能被继承的类
////// 父类的构造声明为私有，不能被继承
////class NoH{
////private: // 构造函数声明为私有的，无法被
////	NoH(){};
////};
////
////// 不能被继承的类：声明为final类
////// 或者这个父类定义为final类
////class NoH2 final{
////
////};
////
////// 单例模式
////// 设计模式:单例模式
////// 饿汉模式
////// 1、构造函数私有
////// 2、提供一个静态的方法返回单例
////// 3、声明一个静态的单例成员
////// 4、拷贝构造和赋值声明为delete函数
////
////// 特点：实现简单，多线程效率高
////// 缺点：程序启动较慢，多个单例对象初始化的顺序无法控制顺序
////
////class singleton{
////public:
////	static singleton* getInstance()
////	{
////		//调用一个存在的对象
////		//给一个静态的对象，主程序启动就创建成功
////		return &_single;
////	}
////private:
////	//构造方法私有
////	singleton(){};
////
////	// 当前成员必须是静态的，非静态不可行
////
////	//不属于对象，不算数据大小
////	// 在类外初始化
////	static singleton _single;
////
////	//防止拷贝的操作
////	singleton(const singleton& slg) = delete;
////	singleton& operator=(const singleton& slg) = delete;
////
////};
////// 静态成员的初始化
////singleton singleton::_single;
////
////
////
////// 懒汉模式：有拖延症
//////构造函数仍然需要私有化
////// 保证线程安全（修改指针），双检查提高效率
////
////// 特点：延迟加载，程序启动快，可以指定多个单例对象的初始化顺序
////// 实现复杂，需要考虑多线程问题
////class Singleton2{
////public:
////	static Singleton2* getInstance(){
////		// 双检查：
////		// 双检查：时间更少，没有那么多阻塞，此时会有质的改变
////		if (_ptr == nullptr){
////			// 上锁的目的就是保证只创建了一个单例，而不是多个
////			_mtx.lock();
////			//需要拿到的是同一个对象
////			if (_ptr == nullptr){
////				// 第一次调用创建对象
////				// 此处的写中多线程导致出现问题
////
////				// 当两个进程同时到此处
////				// 一个进程创建对象赋值给_ptr之后，还没有释放
////				// 第二个进程又来创建对象赋值
////				// 因此需要保证是串行操作
////				_ptr = new Singleton2;
////			}
////			_mtx.unlock();
////		}
////		return _ptr;
////	}
////
////	// 还资源
////	// 可写可不写
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
////	//防拷贝
////	Singleton2(const Singleton2&) = delete;
////	Singleton2& operator=(const Singleton2&) = delete;
////	static Singleton2* _ptr;
////	// 静态和程序的生命周期一致
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
//// 类型转换
//
//void testast(){
//	// 隐式类型转换
//	char c = 'a';
//	int a = c;
//	float f = 1.2f;
//	int d = (int)f;
//
//	//强制转换:类型差别比较大
//	int* ptr = &a;
//	int e = (int)ptr;
//	int * ptr2 = (int*)a;
//
//	//C++增加强转类型
//	// static_cast
//	// reinterpret_cast
//	// const_cast
//	// dynamic_cast
//
//	// static_cast：支持所有隐式类型转换
//	int m = static_cast<int>(c);
//	int d2 = static_cast<int>(f);
//	// static_cast不支持强制类型转换
//	//int* ptr3 = static_cast<int*>(a);
//	int* ptr3 = reinterpret_cast<int*>(a);
//
//	//函数指针与函数之间不匹配也可以用 reinterpret_cast 强转
//
//	// const_cast：去掉const属性
//	const int ca = 10;
//	const int* ptrca = &ca;
//
//	int* ptrca1 = const_cast<int*>(&ca);
//
//	//dynamic_cast：只能用于多态，进行向下转型
//	// 进行安全转换，如果转换不成功，返回空指针
//
//	A* pa = new A;
//	A* pb = new B;
//
//	B* pb2 = (B*)pa;
//
//	//static_cast：父类转子类，不进行安全判断
//	B* pb5 = static_cast<B*>(pa);
//
//	B* pb3 = dynamic_cast<B*>(pa);
//	B* pb4 = dynamic_cast<B*>(pb);
//
//}
//void test(){
//
//}


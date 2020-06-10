#include <iostream>
#include <string>

using namespace std;

template<class T>
class Vector {
public:
	//无参默认构造
	Vector()
		:_start(nullptr)
		,_finish(nullptr)
		,_eos(nullptr)
	{}
	//元素个数
	size_t size() {
		return _finish - _start;
	}
	//容量
	size_t capacity() {
		return _eos - _start;
	}
	//尾插一个字符
	void pushBack(const T& val) {
		//判断容量
		if (_finish == _eos) {
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		*_finish = val;
		++_finish;
	}
	//调整容量
	void reserve(size_t n) {
		if (n > capacity()) {
			size_t oldsize = size();
			//开空间
			T* tmp = new T[n];
			//拷贝内容 : 深拷贝
			for (int i = 0; i < size(); ++i) {
				tmp[i] = _start[i];
			}

			//释放原有空间
			delete[] _start;  //释放空间后原有size不能再使用
			//更新指针
			_start = tmp;
			_finish = _start + oldsize;
			_eos = _start + n;
		}
	}
	//operator[] :可读可写
	T& operator[](size_t pos) {
		if (pos < size())
			return _start[pos];
	}

	//只读接口
	const T& operator[](size_t pos) const{
		if (pos < size())
			return _start[pos];
	}
	//迭代器
	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finish;
	}

	const_iterator begin() const{
		return _start;
	}
	const_iterator end() const{
		return _finish;
	}
	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			//填充
			while (_finish != _start + n) {
				*_finsh++ = val;
			}
		}
		//更新size
		_finish = _start + n;
	}
	//插入
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finish) {
			size_t len = pos - _start;
			if (_finish == _eos) {
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
			}
			pos = _start + len;
			iterator end = _finish;
			while (pos < end) {
				*end = *(end - 1);
				--end;
			}
			//插入元素
			*pos = val;
			++_finish;
		}
	}
private:
	T* _start;
	T* _finish;
	T* _eos; //end_of_stone
};

void test() {
	Vector<int> v;
	v.pushBack(1);
	v.pushBack(2);
	v.pushBack(3);
	v.pushBack(4);
	v.pushBack(5);
	v.pushBack(6);
	v.pushBack(7);
	v.pushBack(8);
	Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//operator[]:
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
	//范围for:
	for (int& ch : v) {
		cout << ch << " ";
	}
	cout << endl;
}

int main() {
	test();
	return 0;
}
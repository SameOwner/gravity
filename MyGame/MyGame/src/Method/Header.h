#pragma once
// ヘルパ関数
template < class Ty >
void* union_cast(Ty ptr)
{ // メンバ関数ポインタをvoid*に変換する
  // reinterpret_castでもできない危険なキャスト
	union
	{
		Ty _mem_func_ptr;
		void* _void_ptr;
	};
	_mem_func_ptr = ptr;
	return _void_ptr;
}

//
// デリゲートクラス
template < class >
class delegate {};
template < class Ret, class... Args >
class delegate < Ret(Args...) >
{
	using _KeyPair = std::pair < void*, void* >;
	struct _Value
	{
		std::function < Ret(Args...) > function;
		_KeyPair keys;
	};
	std::vector < _Value > value;

	auto find(void* first, void* second = nullptr) NOEXCEPT
	{
		_KeyPair arg{ first, second };
		return std::find_if(value.begin(), value.end(), [&](_Value& val)
		{ // lambda
			return val.keys == arg;
		});
	}

public:
	//
	// add function
	//
	template < class Ty >
	void add(Ty* func) // 関数ポインタ用
	{ // function-pointer
		if (find(func) != value.end()) { return; }
		value.push_back({ [=](Args... args) -> Ret
		{ // lambda
			return func(std::forward < Args >(args)...);
		}, _KeyPair(func, nullptr) });
	}
	template < class Ty >
	void add(Ty& func) // 関数オブジェクト用
	{ // function-object
		if (find(&func) != value.end()) { return; }
		value.push_back({ [&](Args... args) -> Ret
		{ // lambda
			return func(std::forward < Args >(args)...);
		}, _KeyPair(&func, nullptr) });
	}
	template < class Ty >
	void add(Ty&& func) // 関数オブジェクト用
	{ // function-object
		value.push_back({ [func = std::move(func)](Args... args) mutable->Ret
		{ // lambda
			return func(std::forward < Args >(args)...);
		}, _KeyPair(nullptr, nullptr) });
	}
	template < class Ty1, class Ty2 >
	void add(Ty1& obj, Ty2 ptr) // メンバ関数ポインタ用
	{ // member-function
		if (find(&obj, union_cast(ptr)) != value.end()) { return; }
		value.push_back({ [&obj, ptr](Args... args) -> Ret
		{ // lambda
			return (obj.*ptr)(std::forward < Args >(args)...);
		}, _KeyPair(&obj, union_cast(ptr)) });
	}

	//
	// remove function
	//
	template < class Ty >
	void remove(Ty* func) // 関数ポインタ用
	{
		auto itr = find(func);
		if (itr != value.end()) { value.erase(itr); }
	}
	template < class Ty >
	void remove(Ty& func) // 関数オブジェクト用
	{
		remove(&func);
	}
	template < class Ty1, class Ty2 >
	void remove(Ty1& obj, Ty2 ptr) // メンバ関数ポインタ用
	{
		auto itr = find(&obj, union_cast(ptr));
		if (itr != value.end()) { value.erase(itr); }
	}

	//
	// invoke functions
	//
	void operator() (Args... args) const
	{
		for (auto&& elem : value) { elem.function(std::forward < Args >(args)...); }
	}
};
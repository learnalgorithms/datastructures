#include <matplotlibcpp.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

class dynamic_array_simple
{
	public:
	void push(int new_value)
	{
		std::unique_ptr<int[]> new_values = std::make_unique<int[]>(size_+1);
		for(std::size_t i=0;i<size_;++i)
			new_values[i] = values_[i];
		
		new_values[size_] = new_value;
		++size_;
		values_ = std::move(new_values);
	}
	
	int& operator[](std::size_t idx) { return values_[idx]; }
	const int& operator[](std::size_t idx) const { return values_[idx]; }
	
	auto size() const { return size_; }
	
	private:
	std::unique_ptr<int[]> values_ = nullptr;
	std::size_t size_ = 0;
};

class dynamic_array_amortizing
{
	public:
	void push(int new_value)
	{
		if(size_==capacity_)
		{
			std::unique_ptr<int[]> new_values = std::make_unique<int[]>(capacity_*2);
			for(std::size_t i=0;i<size_;++i)
				new_values[i] = values_[i];
				
			values_ = std::move(new_values);
			capacity_*=2;
		}
		values_[size_++] = new_value;
	}
	
	int& operator[](std::size_t idx) { return values_[idx]; }
	const int& operator[](std::size_t idx) const { return values_[idx]; }
	
	auto size() const { return size_; }
	
	private:
	std::unique_ptr<int[]> values_ = std::make_unique<int[]>(1);
	std::size_t size_ = 0, capacity_ = 1;
};

std::vector<int> random_n(std::size_t n)
{
	static std::mt19937 random_gen{std::random_device{}()};
	
	std::vector<int> result(n);
	std::iota(std::begin(result),std::end(result),0);
	std::shuffle(std::begin(result),std::end(result),random_gen);
	
	return result;
}

template <typename T>
inline void do_not_optimize(T& value)
{
  asm volatile("" : "+m,r"(value) : : "memory");
}

int main()
{
	namespace plt = matplotlibcpp;
	constexpr std::size_t number_of_push_sets = 100000, number_of_pushes_per_set = 100, number_of_measurements_per_push = 10;

	const auto values = random_n(number_of_push_sets*number_of_pushes_per_set);
	
	std::vector<dynamic_array_simple> simple(number_of_measurements_per_push);
	std::vector<std::size_t> measurements_simple;
	
	std::vector<dynamic_array_amortizing> amortizing(number_of_measurements_per_push);
	std::vector<std::size_t> measurements_amortizing;
	
	std::size_t size = 0;
	for(std::size_t i=0; i<values.size();i+=number_of_pushes_per_set)
	{
		size+=number_of_pushes_per_set;
		
		auto start = std::chrono::high_resolution_clock::now();
		
			for(std::size_t j=i;j<i+number_of_pushes_per_set;++j)
				for(auto& array: simple)
					array.push(values[j]);
			
		auto end = std::chrono::high_resolution_clock::now();
		
		do_not_optimize(simple);
		for(auto& array: simple)
		{
			if(array.size()!=size || !std::equal(&array[0],&array[size],std::begin(values)))
			{
				std::cerr<<"Insert failed!\n";
				return -1;
			}
		}
		
		measurements_simple.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
		
		start = std::chrono::high_resolution_clock::now();
		
			for(std::size_t j=i;j<i+number_of_pushes_per_set;++j)
				for(auto& array: amortizing)
					array.push(values[j]);
				
		end = std::chrono::high_resolution_clock::now();
		
		do_not_optimize(amortizing);
		for(auto& array: amortizing)
		{
			if(array.size()!=size || !std::equal(&array[0],&array[size],std::begin(values)))
			{
				std::cerr<<"Insert failed!\n";
				return -1;
			}
		}
		
		measurements_amortizing.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
	}
	
	
	std::vector<std::size_t> sizes(number_of_push_sets);
	std::generate(std::begin(sizes),std::end(sizes),[n=0]() mutable
	{
		return n+=number_of_pushes_per_set;
	});
	plt::xlabel("Input size");
	plt::ylabel("Time(ms)");
	plt::named_plot("dynamic_array_simple",sizes,measurements_simple);
	plt::named_plot("dynamic_array_amortizing",sizes,measurements_amortizing);
	plt::legend();
	plt::show();
}

#include <matplotlibcpp.h>

#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

void bubble_sort(std::vector<int>& data)
{
	for(std::size_t i=0;i<data.size();++i)
	{
		for(std::size_t j=0;j<data.size()-1;++j)
		{
			if(data[j]>data[j+1])
				std::swap(data[j],data[j+1]);
		}
	}
}

void better_bubble_sort(std::vector<int>& data)
{
	for(std::size_t i=0;i<data.size();++i)
	{
		bool swapped = false;
		for(std::size_t j=0;j<data.size()-1-i;++j)
		{
			if(data[j]>data[j+1])
			{
				std::swap(data[j],data[j+1]);
				swapped = true;
			}
		}
		if(!swapped)
			break;
	}
}

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
	using duration_type = decltype(std::chrono::high_resolution_clock::now()-std::chrono::high_resolution_clock::now());
	constexpr std::size_t number_of_samples = 30;
	
	std::vector<std::size_t> sizes(100);
	std::generate(std::begin(sizes),std::end(sizes),[n=0]() mutable
	{
		return n+=100;
	});
	
	std::vector<std::size_t> ms_durations_sort, ms_durations_better;
	for(auto n: sizes)
	{
		auto data = random_n(n);
		duration_type duration_sort{0}, duration_better{0};
		
		for(std::size_t i=0;i<number_of_samples;++i)
		{
			auto cpy = data;
			const auto start_sort = std::chrono::high_resolution_clock::now();
				bubble_sort(cpy);
			const auto end_sort = std::chrono::high_resolution_clock::now();
			do_not_optimize(cpy);
			
			if(!std::is_sorted(std::begin(cpy),std::end(cpy)))
				std::cerr<<"Sorting failed!\n";
				
			cpy = data;
			const auto start_better = std::chrono::high_resolution_clock::now();
				better_bubble_sort(cpy);
			const auto end_better = std::chrono::high_resolution_clock::now();
			do_not_optimize(cpy);
			
			if(!std::is_sorted(std::begin(cpy),std::end(cpy)))
				std::cerr<<"Sorting failed!\n";
			
			duration_sort+=end_sort-start_sort;
			duration_better+=end_better-start_better;
		}
		
		ms_durations_sort.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(duration_sort).count());
		ms_durations_better.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(duration_better).count());
	}
	
	std::vector<std::size_t> ms_durations_projected;
	
	const auto first = 2*ms_durations_better[50]/static_cast<double>(sizes[50]*sizes[50]-sizes[50]);
	
	for(auto n: sizes)
		ms_durations_projected.push_back(first*(n*n-n)/2);
	
	plt::xlabel("Input size");
	plt::ylabel("Time(ms)");
	plt::named_plot("simple_bubble_sort",sizes,ms_durations_sort);
	plt::named_plot("better_bubble_sort",sizes,ms_durations_better);
	plt::named_plot("projected((n^2-n)/2)",sizes,ms_durations_projected);
	plt::legend();
	plt::show();
}

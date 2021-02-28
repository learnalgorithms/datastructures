#include <matplotlibcpp.h>

#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

template <typename iter_type>
auto partition(iter_type begin, iter_type end)
{
	const auto pivot = begin;

	while(begin<end)
	{
		while(++begin<end && *begin<=*pivot);
			
		while(--end>begin && *end>*pivot);
		
		if(begin<end)
			std::swap(*begin,*end);
	}
	
	std::swap(*pivot,*--begin);
	
	return begin;
}

template <typename iter_type>
void quicksort(iter_type begin, iter_type end)
{
	if(begin>=end)
		return;
		
	const auto partition_point = partition(begin,end);
	quicksort(begin,partition_point);
	quicksort(partition_point+1,end);
}

void quicksort(std::vector<int>& data)
{
	quicksort(std::begin(data),std::end(data));
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
	constexpr std::size_t number_of_samples = 1000, number_of_measurements_per_sample = 10;

	std::vector<std::size_t> sizes(100);
	std::generate(std::begin(sizes),std::end(sizes),[n=0]() mutable
	{
		return n+=100;
	});
	
	using measurement_set = std::array<std::size_t,number_of_samples>;
	std::vector<measurement_set> measurements;
	
	for(auto n: sizes)
	{
		measurement_set measurement;
		for(auto& m: measurement)
		{
			auto data = random_n(n);
			duration_type duration{0};
			
			for(std::size_t i=0;i<number_of_measurements_per_sample;++i)
			{
				auto cpy = data;
				const auto start = std::chrono::high_resolution_clock::now();
					quicksort(cpy);
				const auto end = std::chrono::high_resolution_clock::now();
				do_not_optimize(cpy);
				
				if(!std::is_sorted(std::begin(cpy),std::end(cpy)))
				{
					std::cerr<<"Sorting failed!\n";
					for(auto v: cpy)
						std::cerr<<v<<' ';
					std::cerr<<'\n';
					return -1;
				}
				
				duration+=end-start;
			}
			
			m = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		}
		measurements.push_back(measurement);
	}
	
	std::vector<std::size_t> best, worst, average;
	std::transform(std::begin(measurements),std::end(measurements),std::back_inserter(best),[](const auto& measurement)
	{
		return *std::min_element(std::begin(measurement),std::end(measurement));
	});
	
	std::transform(std::begin(measurements),std::end(measurements),std::back_inserter(worst),[](const auto& measurement)
	{
		return *std::max_element(std::begin(measurement),std::end(measurement));
	});
	
	std::transform(std::begin(measurements),std::end(measurements),std::back_inserter(average),[](const auto& measurement)
	{
		return std::accumulate(std::begin(measurement),std::end(measurement),std::size_t{0})/measurement.size();
	});
	
	plt::xlabel("Input size");
	plt::ylabel("Time(ms)");
	plt::named_plot("quicksort(best)",sizes,best);
	plt::named_plot("quicksort(worst)",sizes,worst);
	plt::named_plot("quicksort(average)",sizes,average);
	plt::legend();
	plt::show();
}

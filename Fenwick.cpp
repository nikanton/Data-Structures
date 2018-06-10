#include <vector>

using VectorInt = std::vector<long long>;

class Fenwick {
private:
	size_t len;
	VectorInt fenwickTree;
	long long subSum(int to) {
		return to >= 0 ? fenwickTree[to] + subSum((to & (to + 1)) - 1) : 0;
	}
public:
	Fenwick(size_t len) : len(len), fenwickTree(VectorInt(len, 0)) {}
	Fenwick(VectorInt elements) : len(elements.size()), fenwickTree(VectorInt(elements.size(), 0)) {
		for (int i = 0; i < len; ++i) {
			add(i, elements[i]);
		}
	}
	void add(int to, long long value) {
		while (to < len) {
			fenwickTree[to] += value;
			to |= to + 1;
		}
	}
	long long sum(int from, int to) {
		return subSum(to) - subSum(from - 1);
	}
};
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define GROUP_QUALITY 40
vector<vector<int>> bestGroup;
int bestUngroupQuality = 999999999;
void FindGroup(vector<vector<int>> &totalGems, vector<vector<int>> &ungroupGems, vector<vector<int>> &groupGems, int iter, int sum);

int main()
{
	vector<int> qualityGems;
	int gem;
	while (cin >> gem) {
		if (gem <= 0) {
			break;
		}
		qualityGems.push_back(gem);
	}

	cout << "CalculatING...." << endl;
	sort(qualityGems.begin(), qualityGems.end());
	vector<vector<int>> totalGems, groupGems, ungroupGems;
	totalGems.push_back(qualityGems);
	groupGems.push_back(vector<int>());
	ungroupGems.push_back(vector<int>());
	FindGroup(totalGems, ungroupGems, groupGems, qualityGems.size() - 1, 0);

	system("pause");
	return 0;
}

void FindGroup(vector<vector<int>> &totalGems, vector<vector<int>> &ungroupGems, vector<vector<int>> &groupGems, int iter, int sum)
{
	if (accumulate(ungroupGems.back().begin(), ungroupGems.back().end(), 0) > bestUngroupQuality) {
		return;
	}
	for (int i = iter; i >= 0; i--) {
		if (sum + totalGems.back()[i] == GROUP_QUALITY) {
			groupGems.back().push_back(totalGems.back()[i]);
			totalGems.push_back(totalGems.back());
			for (int gem : groupGems.back()) {
				totalGems.back().erase(find(totalGems.back().begin(), totalGems.back().end(), gem));
			}
			ungroupGems.push_back(ungroupGems.back());
			groupGems.push_back(vector<int>());
			FindGroup(totalGems, ungroupGems, groupGems, totalGems.back().size() - 1, 0);
			groupGems.pop_back();
			totalGems.pop_back();
			ungroupGems.pop_back();
			groupGems.back().pop_back();
		}
		else if (sum + totalGems.back()[i] < GROUP_QUALITY) {
			groupGems.back().push_back(totalGems.back()[i]);
			FindGroup(totalGems, ungroupGems, groupGems, i-1, sum+totalGems.back()[i]);
			groupGems.back().pop_back();
		}
		if (sum == 0) {
			ungroupGems.back().push_back(totalGems.back()[i]);
			totalGems.back().erase(totalGems.back().begin() + i);
		}
	}
	if (sum == 0) {
		int ungroupQuality = accumulate(ungroupGems.back().begin(), ungroupGems.back().end(), 0);
		if (ungroupQuality < bestUngroupQuality) {
			groupGems.back() = ungroupGems.back();
			bestUngroupQuality = ungroupQuality;
			bestGroup = groupGems;
			cout << "§ä¨ì¤@²Õ" << endl;
			for (vector<int> group : bestGroup) {
				for (int gem : group) {
					cout << gem << " ";
				}
				cout << endl;
			}
			if (bestUngroupQuality < 40) {
				system("pause");
				exit(0);
			}
		}
	}
	return;
}

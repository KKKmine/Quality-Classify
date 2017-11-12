#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define GROUP_QUALITY 40
vector<vector<int>> bestGroup;
int bestUngroupQuality = 999999999;
void FindGroup(vector<vector<int>> &totalGems, vector<vector<int>> &groupGems, int iter, int groupIter, int sum);

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
	vector<vector<int>> totalGems, groupGems;
	totalGems.push_back(qualityGems);
	groupGems.push_back(vector<int>());
	FindGroup(totalGems, groupGems, qualityGems.size() - 1, qualityGems.size() - 1, 0);

	system("pause");
	return 0;
}

void FindGroup(vector<vector<int>> &totalGems, vector<vector<int>> &groupGems, int iter, int groupIter, int sum)
{
	for (int i = iter; i >= 0; i--) {
		if (sum + totalGems.back()[i] == GROUP_QUALITY) {
			groupGems.back().push_back(totalGems.back()[i]);
			totalGems.push_back(totalGems.back());
			for (int gem : groupGems.back()) {
				totalGems.back().erase(find(totalGems.back().begin(), totalGems.back().end(), gem));
			}
			groupIter -= groupGems.back().size();
			groupGems.push_back(vector<int>());
			FindGroup(totalGems, groupGems, groupIter, groupIter, 0);
			groupGems.pop_back();
			totalGems.pop_back();
			groupGems.back().pop_back();
		}
		else if (sum + totalGems.back()[i] < GROUP_QUALITY) {
			groupGems.back().push_back(totalGems.back()[i]);
			FindGroup(totalGems, groupGems, i-1, groupIter, sum+totalGems.back()[i]);
			groupGems.back().pop_back();
		}
		if (sum == 0) {
			groupIter--;
		}
	}
	if (sum == 0) {
		int ungroupQuality = accumulate(totalGems.back().begin(), totalGems.back().end(), 0);
		if (ungroupQuality < bestUngroupQuality) {
			groupGems.back() = totalGems.back();
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

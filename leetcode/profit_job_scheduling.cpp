#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> p;

void printIntVector(vector<int> &v)
{
  for (int i = 0; i < v.size(); i++)
  {
    printf("%d ", v[i]);
  }
}

bool compProfit(const int &a, const int &b)
{
  if (p[a] > p[b])
  {
    return true;
  }
  return false;
}

class Solution
{
public:
  static int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
  {
    p = profit;
    int maxTime = *max_element(begin(endTime), end(endTime));
    vector<bool> filledSchedule(maxTime, false);
    int totalProfit = 0;
    vector<int> sortedProfitsIndexes(profit.size());
    iota(begin(sortedProfitsIndexes), end(sortedProfitsIndexes), 0);
    sort(begin(sortedProfitsIndexes), end(sortedProfitsIndexes), compProfit);
    for (int i = 0; i < sortedProfitsIndexes.size(); i++)
    {
      int profitIdx = sortedProfitsIndexes[i];
      vector<int> sortedIndexesWithout = sortedProfitsIndexes;
      sortedIndexesWithout.erase(sortedIndexesWithout.begin() + i);
      cout << "i = " << profitIdx << "-> [" << startTime[profitIdx] << ", " << endTime[profitIdx] << "]" << endl;
      int tempProfit = profit[profitIdx];
      int j;
      for (j = startTime[profitIdx] - 1; j < endTime[profitIdx] - 1; j++)
      {
        filledSchedule[j] = true;
      }
      for (j = 0; j < sortedIndexesWithout.size(); j++)
      {
        int secondaryProfitIdx = sortedProfitsIndexes[j];
        cout << "j = " << secondaryProfitIdx << "-> [" << startTime[secondaryProfitIdx] << ", " << endTime[secondaryProfitIdx] << "]" << endl;
        bool hasRoomInSchedule = true;
        int k = startTime[secondaryProfitIdx] - 1;
        while (k < endTime[secondaryProfitIdx] - 1)
        {
          if (filledSchedule[k])
          {
            hasRoomInSchedule = false;
            break;
          }
          k++;
        }
        cout << "hasRoomInSchedule = " << hasRoomInSchedule << endl;
        cout << "profit[" << secondaryProfitIdx << "] = " << profit[secondaryProfitIdx] << endl;
        if (!hasRoomInSchedule)
        {
          continue;
        }
        else
        {
          tempProfit += profit[secondaryProfitIdx];
          cout << "tempProfit = " << tempProfit << endl;
          k = startTime[secondaryProfitIdx] - 1;
          while (k < endTime[secondaryProfitIdx] - 1)
          {
            filledSchedule[k] = true;
            k++;
          }
        }
      }
      if (tempProfit > totalProfit)
        totalProfit = tempProfit;
      filledSchedule.assign(maxTime, false);
      cout << endl;
    }
    return totalProfit;
  }
};

int main()
{
  int startTime[] = {15, 44, 15, 47, 11, 18, 5, 41, 38, 25, 19, 25};
  int endTime[] = {33, 48, 20, 49, 37, 22, 32, 48, 39, 37, 38, 40};
  int profit[] = {18, 19, 16, 1, 5, 12, 17, 7, 19, 9, 18, 9};

  vector<int> startTimeVec;
  vector<int> endTimeVec;
  vector<int> profitVec;
  for (int i = 0; i < sizeof(startTime) / sizeof(startTime[0]); i++)
  {
    startTimeVec.push_back(startTime[i]);
    endTimeVec.push_back(endTime[i]);
    profitVec.push_back(profit[i]);
  }
  int res = Solution::jobScheduling(startTimeVec, endTimeVec, profitVec);
  cout << res;
}
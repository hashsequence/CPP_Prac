// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED
#include<unordered_map>
#include<vector>

string hashCells(vector<int> cells); 

vector<int> cellCompete(int* states, int days) 
{
    vector<int> cells;
    // WRITE YOUR CODE HERE  
    if (days == 0) {
        return cells ;
    }
    bool cycleDetected = false;
    unordered_map<int,vector<int>> daysToCells;
    unordered_map<string,bool> isSeen;
   
    for (int i = 0; i < 8; i++) {
        cells.push_back(states[i]);
    }
    int k = 0;
    for (; k <= days; k++) {
        string hashStr = hashCells(cells);
        if (isSeen[hashStr] == false && k != 0) {
            isSeen[hashStr] = true;
            daysToCells[k] = cells;
        } else {
            if (k != 0) {
                cycleDetected = true;
                k--;
                break;
            }
        }
        vector<int> nextCells(cells);
        for (int i = 0; i < 8; i++) {
            if ((i == 0 && cells[1] == 0) || (i == 7 && cells[6] == 0)) {
                nextCells[i] = 0;
            } else if (i > 0 && i < 7 && cells[i-1] == cells[i+1]) {
                nextCells[i] = 0;
            } else {
                nextCells[i] = 1;
            }
        }
        cells = nextCells;
        
    }
    if (!cycleDetected) {
            return daysToCells[days];
    }
        
    daysToCells[0] = daysToCells[k];
    return daysToCells[(days-k) % k];

    
    
}

string hashCells(vector<int> cells) {
    string s = "";
     for (int i = 0; i < 8; i++) {
      if (cells[i] == 1) {
          s += '1';
      } else {
          s += '0';
      }
    }
    cout << s << endl;
    return s;
}
// FUNCTION SIGNATURE ENDS

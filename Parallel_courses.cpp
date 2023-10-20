/*
You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], 
representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei. Also, you are given the integer k.
In one semester, you can take at most k courses as long as you have taken all the prerequisites in the previous semesters for the courses you are taking.
Return the minimum number of semesters needed to take all courses. The testcases will be generated such that it is possible to take every course.
*/


class Solution {
public:
    int dfs(int n,vector<int>adj[],int k,int mask,int cur,vector<int>&dp){
        if(cur==mask) return 0;
        if(dp[cur]!=-1) return dp[cur];
        vector<int>in(n,0);
        for(int i=0;i<n;i++){
            if((1<<i)&cur) continue;     //so that those courses which have been 
            // included does not affect indegree of remaining course
            for(auto j:adj[i]) in[j]++;
        }
        int temp=0,c=0;
        for(int i=0;i<n;i++)    if(in[i]==0&&!(cur&(1<<i))) temp|=(1<<i),c++;
        int ans=n+1;
        if(c<=k) ans = min(ans,dfs(n,adj,k,mask,cur|temp,dp)+1); //take all courses
        else{
            for(int j=temp;j>0;j=(j-1)&temp){
                if(__builtin_popcount(j)!=k) continue;
                ans = min(ans,dfs(n,adj,k,mask,cur|j,dp)+1);   //take a subset of 
                // courses having exactly k courses
            }
        }
        return dp[cur] = ans;
    }
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int>adj[n];
        for(int i=0;i<relations.size();i++){
            adj[relations[i][0]-1].push_back(relations[i][1]-1);
        }
        int mask = (1<<n)-1;
        // WE CAN'T APPLY TOPOSORT DIRECTLY AS WE DON'T KNOW WHICH K COURSES TO CHOOSE
        // IF NUMBER OF COURSES AT A CURRENT DEGREEE IS > K
        vector<int>dp(1<<n,-1);
        return dfs(n,adj,k,mask,0,dp);
    }
};

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string>   result;
    std::string                line;
    std::getline(str,line);

    std::stringstream          lineStream(line);
    std::string                cell;

    while(std::getline(lineStream,cell, ','))
    {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }
    return result;
}

class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   

template<typename V, typename E>
class Graph
{
public:
	using VertexID = size_t;

	VertexID addVertex(V);
	Graph& addEdge(VertexID, VertexID, E);

	void roadDistance()
	{
        size_t length = 1;
        std::queue<User> Qvisited1;
        std::queue<User> Qvisited2;

        std::unordered_map<User::ID, bool> visited1;
        std::unordered_map<User::ID, bool> visited2;

        visited1[id_] = 1;
        visited2[goalFriend.id_] = 1;

        for(auto i:  roadDistance)
        {
            Qvisited1.push(*i.second);
        }
        for(auto i: roadDistance)
        {
            Qvisited2.push(*i.second);
        }

        return BI_BFS(Qvisited1, Qvisited2, visited1, visited2, length);
	}

	/* ... */

	    //!Bi-Directional Breath First Search
    size_t BI_BFS(std::queue<User> Qvisited1, std::queue<User> Qvisited2, std::unordered_map<User::ID, bool> visited1,
               std::unordered_map<User::ID, bool> visited2, size_t length) const
    {
        size_t result  = 0;
        int flag = 1;
        while(!Qvisited1.empty() and !Qvisited2.empty())
        {
            //flag accounts for first case of length 1
            result = BFS(Qvisited1, visited1, visited2, length, flag);
            if(result) { return result; }

            result = BFS(Qvisited2, visited2, visited1, length, 0);
            if(result) { return result; }
            flag = 0;
        }
        //there is no connection between friends
        return SIZE_MAX;
    }


    //!Preform one Iteration of a Breath First Search
    size_t BFS(std::queue<User> &Qvisited, std::unordered_map<User::ID, bool> &map1,
               std::unordered_map<User::ID, bool> &map2, size_t &length, int flag) const
    {
        length++;
        auto Qsize = Qvisited.size();
        size_t result = 0;
        if(Qsize > 0)
        {
            result = BFS_Friends(Qvisited, map1, map2, length, flag);
            if(result) { return result; }

            result = BFS_Friends_Friends(Qvisited, map1, map2, length, flag);
            if(result) { return result; }
        }
        return 0;
    }

    //!Search friends for path
    size_t BFS_Friends(std::queue<User> &Qvisited,  std::unordered_map<User::ID, bool> &map1,
                       std::unordered_map<User::ID, bool> &map2, size_t &length, int flag) const
    {
        auto Qsize = Qvisited.size();
        User currentUser = Qvisited.front();
        //iterate through queue and check if any imitate friends are goal friend
        for(auto i = 0; i < Qsize; i++)
        {
            currentUser = Qvisited.front();
            Qvisited.pop();
            map1[currentUser.id_] = 1;
            //check if visited yet (path found)
            if (map2[currentUser.id_] == 1)
            {
                return length - flag;
            }
            Qvisited.push(currentUser);
        }
        return 0;
    }

    //!Search friends of friends for path
    size_t BFS_Friends_Friends(std::queue<User> &Qvisited,  std::unordered_map<User::ID, bool> &map1,
                       std::unordered_map<User::ID, bool> &map2, size_t &length, int flag) const
    {
        auto Qsize = Qvisited.size();
        User currentUser = Qvisited.front();
        //iterate through friends friends and check if any are goal friend
        for(auto i = 0; i < Qsize; i++)
        {
            currentUser = Qvisited.front();
            Qvisited.pop();
            for(auto j: currentUser.friends)
            {
                //Check if visited yet (path found)
                if(map2[j.first] == 1)
                {
                    return length + 1 - flag;
                }
                //if we haven't visited this friend yet, add them to queue to be visited
                if(map1[j.first] == 0)
                {
                    map1[j.first] = 1;
                    Qvisited.push(*(j.second));
                }
            }
        }
        return 0;
    }

};
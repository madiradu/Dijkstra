#include <list>
#include <map>
#include <climits>
#include <iostream>
#include <set>
#include <fstream>
#include<string>
#include<queue>
class arbore {
public:
	arbore(long id1)
	{
		id = id1;
	}
	long getID()
	{
		return id;
	}
	std::map<arbore*,double> neighbours;
private:
	arbore();
	long id;
};

std::map<long, arbore*> ids;
void insertArbore(long id1, long id2, double cost)
{
	if (id1 == id2)
		return;
	if (cost == 0)
		return;
	arbore* address1 = NULL;
	arbore* address2 = NULL;
	if (ids.find(id1) != ids.end())
	{
		address1 = ids[id1];
	}
	if (ids.find(id2) != ids.end())
	{
		address2 = ids[id2];
	}
	if ((address1 == NULL)&& (address2 == NULL))
	{
		arbore* a = new arbore(id1);
	    arbore * b = new arbore(id2);
		ids[id1] = a;
		ids[id2] = b;
		a->neighbours[b] = cost;
	    b->neighbours[a]=cost;
	}
	else if ((address1 == NULL))
	{
		arbore* a = new arbore(id1);
		ids[id1] = a;
		a->neighbours[(arbore*)ids[id2]] = cost;
		((arbore*)(ids[id2]))->neighbours[a]=cost;
	}
	else if ((address2 == NULL))
	{
		arbore* b = new arbore(id2);
	    ids[id2] = b;
		b->neighbours[(arbore*)ids[id1]] = cost;
		((arbore*)(ids[id1]))->neighbours[b] = cost;
	}
	else
	{
		((arbore*)ids[id2])->neighbours[(arbore*)ids[id1]] = cost;
		((arbore*)(ids[id1]))->neighbours[(arbore*)ids[id2]] = cost;
	}
}
class Compare
{
public:
	bool operator() (const std::pair<long, double>& pair1, const std::pair<long, double>& pair2)
	{
		return (pair1.second > pair2.second);
	}
};
void djikstra(long id1, long id2,std::map<long,double> &dist, std::map<long,long> &previous)
{
	typedef std::pair<long, double> QueueItem;
	std::priority_queue <QueueItem, std::vector<QueueItem>, Compare > Q;

	dist[id1] = 0;
	for (long v = 0; v < ids.size(); v++)
	{
		previous[v] = -1;
		if (v != id1) {
			dist[v] = INT_MAX;
		}
		Q.push(std::pair<long, double>(v, dist[v]));
	}
	while (!Q.empty())
	{
		//int min = INT_MAX;
		//int u = -1;
/*		for (int k = 0; k < ids.size(); k++)
		{
			if (dist[k] < min)
			{
				if (std::find(Q.begin(), Q.end(), k) != Q.end())
				{
					u = k;
				}
			}
		
		}
		Q.erase(u);*/
		long u = Q.top().first;
		Q.pop();

		for (std::pair<arbore*, double> p : ((arbore*)ids[u])->neighbours)
		{
			arbore *v1 = p.first;
			long v = v1->getID();
			double alt = dist[u] + p.second;
			if (alt < dist[v])
			{
				dist[v] = alt;
				previous[v] = u;
				Q.push(std::pair<long, double>(v,alt));
			}
		}
	}
}
int main()
{
	/*std::ofstream myfile1;
	myfile1.open("input.txt");
	for (int i = 0; i < 100000; i++)
	{
		myfile1 << i << " " << i + 1 << " " << 1 << std::endl;
		myfile1 << i << " " << i + 2 << " " << 2000 << std::endl;
		myfile1 << i << " " << i + 3 << " " << 30000 << std::endl;
	}
	myfile1.close();*/

	//int matrices[7][7] = { {0,2,6,0,0,0,0,},{0,0,0,5,0,0,0},{6,0,0,8,0,0,0},{0,5,8,0,0,0,0},{0,0,0,10,0,6,2},{0,0,0,15,6,0,6},{0,0,0,0,2,6,0} };
	std::ifstream myfile;
	myfile.open("input.txt");
	try {
		std::string myText;
		while (std::getline(myfile, myText)) {
			long i = 0, j = 0;
			int value = 0;
			i = atoi(myText.substr(0, myText.find(' ')).c_str());
			myText = myText.substr(myText.find(' ')+1);
			j = atoi(myText.substr(0, myText.find(' ')).c_str());
			myText = myText.substr(myText.find(' ')+1);
			value = atoi(myText.c_str());

			insertArbore(i, j, value);
		}
	}
	catch (std::exception ex)
	{
		std::cout << "Exception"<<std::endl;
	}
	catch (int a)
	{
		std::cout << "Exception" << std::endl;
	}
	myfile.close();
	/*for (int i = 0; i <= 6; i++)
		for (int j = 0; j <= 6; j++)
		{
			insertArbore(i, j, matrices[i][j]);
		}*/

	std::map<long, double> dist;
	std::map<long, long> previous;
	djikstra(0,99999,dist, previous);
	//djikstra(0, 6, dist, previous);
	std::list<long> s;
	long u = 99999;
	//long u = 6;
	if (((previous.find(u)) != previous.end()) || u == 0)
	{
		while (u != 0)
		{
			s.insert(s.begin(), u);
			u = previous[u];
		}
	}
	for(long index:s)
		std::cout << index << " ";
	std::cout << std::endl;




}
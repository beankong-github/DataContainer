#include "AStar.h"
#include "Node.h"

AStar::AStar()
{

}

AStar::~AStar()
{
	for (Node* n : openList)
	{
		SafeDelete(n);
	}
	openList.clear();

	for (Node* n : closeList)
	{
		SafeDelete(n);
	}
	closeList.clear();
}

vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const vector<vector<int>>& grid)
{
	this->startNode = startNode;
	this->targetNode = goalNode;

	// ���� ��带 ���� ��Ͽ� ����
	openList.emplace_back(startNode);

	while (!openList.empty())
	{
		// ���� ����� ���� ��� ����
		// �켱 ���� ť(��)�� ����ȭ ����
		Node* lowestNode = openList[0];
		for (auto node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		Node* currentNode = lowestNode;

		// ���� ��尡 ��ǥ ������� ����
		// ��ǥ ����� ���� �����ؼ� ��ȯ���ش�.
		if (IsDestination(currentNode))
			return ConstructPath(currentNode);

		// ���� ���->�湮�� ���
		// ���� ��带 ���� ��Ͽ��� ����
		for (int ix = 0; ix < (int)openList.size(); ++ix)
		{
			// ��ġ ��
			if (*openList[ix] == *currentNode)
			{
				// ���� ��Ͽ��� ����
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		// ���� ��带 ���� ��Ͽ� �߰�
		// �̹� ������ �߰� ���ϰ� ������ �߰�
		bool isNodeInList = false;
		for (Node* node : closeList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		// �湮 ������ �Ʒ� �ܰ� �ǳ� �ٱ�
		if (isNodeInList)
		{
			continue;
		}
		
		// ���� ����Ʈ�� �߰�
		closeList.emplace_back(currentNode);

		// �̿� ������ ���� ����Ʈ�� �ִ´�.
		// �����¿� �밢�� ���� �� ���
		static const vector<Direction> directions =
		{
			// �ϻ����
			{0, 1, 1.0f},  {0, -1, 1.f}, {1, 0, 1.f}, {-1, 0, 1.f},
			// �밢��
			{1, 1, 1.414f}, {1, -1, 1.414f}, {-1, 1, 1.414f}, {-1, -1, 1.414f}

		};
		for (const auto& dir : directions)
		{
			// ���� �̵��� ��ġ
			int nextX = currentNode->pos.x + dir.x;
			int nextY = currentNode->pos.y + dir.y;

			//�׸��� ���� ��ȿ�� �ε��� ������ Ȯ��
			if (!IsInRange(nextX, nextY, grid))
				continue;

			// ���� 1�̸� ��ֹ��̶�� ���
			// ��ֹ��� �湮���� �ʴ´�.
			if (grid[nextY][nextX] == 1)
				continue;

			// �̹� �湮�� ���� �湮���� �ʴ´�.
			float gCost = currentNode->gCost + dir.cost;
			if (HasVisited(nextX, nextY, gCost))
			{
				continue;
			}

			// �湮�� ���� ��� ����
			// ��� ���
			Node* neighborNode = new Node(nextX, nextY, currentNode);
			neighborNode->gCost = gCost;
			// �޸���ƽ ��� 
			neighborNode->hCost = CalculateHeuristic(neighborNode, targetNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;


			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			if (openListNode == nullptr
				|| openListNode->gCost > neighborNode->gCost
				|| openListNode->fCost > neighborNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}
		}

	}
	return vector<Node*>();
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	for (const Node* node : path)
	{
		// ��δ� '2'�� ǥ��.
		grid[node->pos.y][node->pos.x] = 2;
	}

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			// ���.
			else if (grid[y][x] == 2)
			{
				std::cout << "* ";
			}

			// �� ����.
			else if (grid[y][x] == 0)
			{
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}

vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	// ��θ� ��ȯ�ϴ� �Լ� ���� ����
	// ��¿� ��� �迭 ����
	vector<Node*> path;

	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	// ���ݱ����� ��δ� ��ǥ->���� ��� ����
	// ����->��ǥ�� ������� �Ѵ�.
	std::reverse(path.begin(), path.end());
	return path;
}

bool AStar::IsDestination(const Node* node)
{
	// ��ġ �� ��� ��ȯ
	return *node == *targetNode;
}

bool AStar::IsInRange(int x, int y, const vector<vector<int>>& grid)
{
	// x, y ������ ����� false.
	if (x < 0 || y < 0 || x >= grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	// ����� ������ true
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��尡 ������ �湮�� ������ �Ǵ��Ѵ�.

	// ���� ����Ʈ���� �˻�
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if (node->pos.x == x && node->pos.y == y)
		{
			// ��ġ�� ����, ��뵵 �� ũ�� �湮�� ���� ����
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + ix);
				SafeDelete(node);
			}
		}
	}
	
	// ���� ����Ʈ���� �˻�
	for (int ix = 0; ix < (int)closeList.size(); ++ix)
	{
		Node* node = closeList[ix];
		// ��ġ�� ����, ��뵵 �� ũ�� �湮�� ���� ����
		if (node->pos.x == x && node->pos.y == y)
		{
			if (node->gCost < gCost)
			{
				return true;
			}
			else if(node->gCost > gCost)
			{
				closeList.erase(closeList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	// ��Ͽ� ���ٰ� Ȯ�εǸ� �湮���� ���� ������ �Ǵ�.
	return false;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* targetNode)
{
	Position diff = *currentNode - *targetNode;
	// �밢�� ���� ��ȯ
	return (float)std::sqrt(diff.x*diff.x + diff.y*diff.y);
}

#include "Grid.h"

Grid::Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos): GameObject(pos)
{

	nodeDiameter = noderadius * 2;
	gridSize = gridsize;
	position = pos;

	gridX = int(gridSize.x / nodeDiameter);
	gridY = int(gridsize.y / nodeDiameter);

	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "boundingbox";
}

void Grid::buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader)
{							
	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 forwardVector = glm::vec3(0, 0, 1);
	glm::vec3 rightVector = glm::cross(upVector, forwardVector);


	glm::vec3 bottomLeft = position - rightVector * (gridSize.x / 2) - forwardVector * (gridSize.y / 2);

	for (int i = 0; i < gridX; i++) {
		std::vector<Node*> columnVector;
		for (int j = 0; j < gridY; j++) {

			//find node position and initialise it to a temporary node
			glm::vec3 nodePos = bottomLeft + rightVector * (i* nodeDiameter + (nodeDiameter / 2)) + forwardVector * (j * nodeDiameter + (nodeDiameter / 2));
			Node *tmpNode = new Node();
			tmpNode->position = nodePos;
			tmpNode->gridX = i;
			tmpNode->gridY = j;

			//////create object to represent node
			//GameObject* gridsquare;
			//gridsquare = new Player(cube);
			//gridsquare->setShader(shader);
			//gridsquare->Move(glm::vec3(tmpNode.position.x, 0.5f , tmpNode.position.z));
			//gridsquare->Scale(glm::vec3(10.0, 1.0, 10.0));
			//gridsquare->setAnim(0);

			std::vector<GameObject*>::iterator it;

			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				if ((*it)->getCollider())
				{
					if (checkaltGridCollision(*it, *tmpNode) == true)
					{
						//gridsquare->Move(glm::vec3(0.0f, 5.0f, 0.0f)); // to check the bastard is working
						tmpNode->setBlocked(true);
						break;
					}
				}
			}
			//add game object to the render loop
			//gameObjects.push_back(gridsquare);

			//add the node to the column
			columnVector.push_back(tmpNode);
		}
		//add the column to the row
		rowVector.push_back(columnVector);
	}
}

void Grid::updateGrid(std::vector<GameObject*> &gameObjects, Shader* shader)
{
	//iterate through each row
	std::vector<std::vector<Node*>>::iterator it;
	for (it = rowVector.begin(); it != rowVector.end(); it++)
	{
		//iterate through each colum of each row
		std::vector<Node*>::iterator it1;
		for (it1 = (*it).begin(); it1 != (*it).end(); it1++)
		{
			std::vector<GameObject*>::iterator it2;
			for (it2 = gameObjects.begin(); it2 != gameObjects.end(); it2++)
			{
				//cycle through all the game objects
				if ((*it2)->getCollider())
				{
					//check
					if (checkaltGridCollision(*it2, **it1) == true)
					{
						cout << "getting here" << endl;
						if ((**it1).getBlocked() == false)
						{
							GameObject* gridsquare;
							gridsquare = new Player(cube);
							gridsquare->setShader(shader);
							gridsquare->Scale(glm::vec3(10.0, 10.0, 1.0));
							gridsquare->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
							gridsquare->Move(glm::vec3((**it1).position.x, -17.5f, (**it1).position.z));
							gridsquare->setAnim(0);
							gameObjects.push_back(gridsquare);
							(**it1).setBlocked(true);
							cout << "checker " << endl;
						}
					}
				}
			}
		}

	}
}

bool Grid::checkaltGridCollision(GameObject* a, Node b)
{

	if (abs(a->getCollider()->getPos().x - b.position.x) > (a->getCollider()->getHW() + (nodeDiameter / 2))) return false;
	if (abs(a->getCollider()->getPos().z - b.position.z) > (a->getCollider()->getHH() + (nodeDiameter/2))) return false;

	return true;
}
bool Grid::checkGridCollision(GameObject* a, Node* b)
{
		// Basic 2D collsion detection

		if (abs(a->getCollider()->getPos().x - b->position.x) > (a->getCollider()->getHW() + (nodeDiameter/2))) return false;
		if (abs(a->getCollider()->getPos().z - b->position.z) > (a->getCollider()->getHH() + (nodeDiameter / 2))) return false;
		return true;

}
void Grid::update()
{

}


glm::vec3 Grid::getPosition()
{
	return position;
}

float Grid::getSize()
{
	return nodeDiameter / 2;
}


Node* Grid::getNodeFromPoint(glm::vec3 point)
{
	float xPercentage = (point.x + gridSize.x / 2) / gridSize.x;
	float zPercentage = (point.z + gridSize.y / 2) / gridSize.y;

	xPercentage = clamp(xPercentage, 1, 0);
	zPercentage = clamp(zPercentage, 1, 0);
	
	int x = round((gridX - 1)*xPercentage);
	int y = round((gridY - 1)*zPercentage);

	cout << x <<" " <<  y << endl;
	return rowVector.at(x).at(y);
}

float Grid::clamp(float n, float upper, float lower)
{
	if (n > upper)
		return upper;
	if (n < lower)
		return lower;

	return n;
}

void Grid::AStarPath(glm::vec3 start, glm::vec3 finish, std::vector<GameObject*>& gameObjects, Shader* shader)
{

	float currentSpot = 0;
	Node *startNode = new Node();
	startNode = getNodeFromPoint(start);
	Node *endNode = new Node();
	endNode = getNodeFromPoint(finish);

	std::vector<Node*> openSet;
	std::vector<Node*> closedSet;

	openSet.push_back(startNode);
	
	while (openSet.size() > 0) {
		Node* current = new Node();
		current = openSet.at(0);
		currentSpot = 0;
		for (int i = 1; i < openSet.size(); i++)
		{
			if (openSet.at(i)->fCost < current->fCost || openSet.at(i)->fCost == current->fCost && openSet.at(i)->hCost < current->hCost) {
				current = openSet.at(i);
				currentSpot = i;
			}
		}

		openSet.erase(openSet.begin() + currentSpot);
		closedSet.push_back(current);

		if (current->gridX == endNode->gridX && current->gridY == endNode->gridY)
		{
//			closedSet.back()->SetParent(closedSet.back() - 1);
			endNode = closedSet.back();
			retracePath(startNode, endNode, gameObjects, shader);
			return;
		}


		for each (Node* neighbour in getNeighbour(current))
		{
			std::vector<Node*>::iterator it;

			bool containsNeighbourClosed = false;
			for (it = closedSet.begin(); it != closedSet.end(); it++)
			{
				if ((**it).gridX == neighbour->gridX && (**it).gridY == neighbour->gridY)
				{
					containsNeighbourClosed = true;
				}
			}
			if (neighbour->getBlocked() == true || containsNeighbourClosed == true)
			{
				continue;
			}

			int newMovementCost = current->gCost + getDistance(*current, *neighbour);
			std::vector<Node*>::iterator it1;

			bool containsNeighbourOpen = false;

			for (it1 = openSet.begin(); it1 != openSet.end(); it1++)
			{
				if ((**it1).gridX == neighbour->gridX && (**it1).gridY == neighbour->gridY)
				{
					containsNeighbourOpen = true;
				}
			}
			
			if (newMovementCost < neighbour->gCost || containsNeighbourOpen == false) {
				neighbour->gCost = newMovementCost;
				neighbour->hCost = getDistance(*current, *endNode);
				neighbour->SetParent(current);
				cout << "spot check" << endl;
				neighbour->getFCost();

				if (containsNeighbourOpen == false && neighbour->getBlocked() == false)
				{
					openSet.push_back(neighbour);
				
				}
			}
		}
	}
}

std::vector<Node*> Grid::getPath()
{
	return path;
}

int Grid::getDistance(Node nodeA, Node nodeB)
{
	int distX = std::abs(nodeA.gridX - nodeB.gridX);
	int distY = std::abs(nodeA.gridY - nodeB.gridY);

	if (distX > distY)
	{
		return 14 * distY + 10 * (distX - distY);
	}
	return 14 * distX + 10 * (distY - distX);
}

std::vector<Node*> Grid::getNeighbour(Node* current)
{
	std::vector<Node*> neighbours;

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0) {
				continue;
			}

			int checkX = current->gridX + x;
			int checkY = current->gridY + y;

			if (checkX >= 0 && checkX < gridSize.x && checkY >= 0 && checkY < gridSize.y && rowVector.at(checkX).at(checkY)->getBlocked() == false)
			{
				neighbours.push_back(rowVector.at(checkX).at(checkY));
			}
		}
	}

	return neighbours;
}

void Grid::retracePath(Node* startNode, Node* endNode, std::vector<GameObject*>& gameObjects, Shader* shader)
{
	GameObject* gridsquare;
	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "boundingbox";

	std::vector<Node*> path;
	Node *currentNode = new Node();
	currentNode = endNode;

	while (currentNode->gridX != startNode->gridX && currentNode->gridY != startNode->gridY)
	{
		path.push_back(currentNode);

		gridsquare = new Player(cube);
		gridsquare->setShader(shader);
		std::cout << currentNode->position.x << " " << currentNode->position.z << std::endl;
		gridsquare->Move(glm::vec3(currentNode->position.x, 1.0f, currentNode->position.z));
		gridsquare->Scale(glm::vec3(10.0, 1.0, 10.0));
		gridsquare->setAnim(0);
		gameObjects.push_back(gridsquare);

		currentNode = currentNode->getParent();

	}
}
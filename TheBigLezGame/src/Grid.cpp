#include "Grid.h"

Grid::Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos): GameObject(pos)
{

	nodeDiameter = noderadius * 2;
	gridSize = gridsize;
	position = pos;

	gridX = int(gridSize.x / nodeDiameter);
	gridY = int(gridsize.y / nodeDiameter);

	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "anything";
}

void Grid::buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader)
{							
	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 forwardVector = glm::vec3(0, 0, 1);
	glm::vec3 rightVector = glm::cross(upVector, forwardVector);


	glm::vec3 bottomLeft = position - rightVector * (gridSize.x / 2) - forwardVector * (gridSize.y / 2);
	//thisGrid = new Node*[gridX]; 
	for (int i = 0; i < gridX; i++) {
		std::vector<Node> columnVector;
		for (int j = 0; j < gridY; j++) {

			//find node position and initialise it to a temporary node
			glm::vec3 nodePos = bottomLeft + rightVector * (i* nodeDiameter + (nodeDiameter / 2)) + forwardVector * (j * nodeDiameter + (nodeDiameter / 2));
			Node tmpNode;
			tmpNode.position = nodePos;

			//create object to represent node
			GameObject* gridsquare;
			gridsquare = new Player(cube);
			gridsquare->setShader(shader);
			//gridsquare->Scale(glm::vec3(10.0, 1.0, 10.0));
			//gridsquare->Rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			gridsquare->Move(glm::vec3(tmpNode.position.x, 0.5f , tmpNode.position.z));
			gridsquare->Scale(glm::vec3(10.0, 1.0, 10.0));
			gridsquare->setAnim(0);

			std::vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{

				if ((*it)->getCollider())
				{
					if (checkaltGridCollision(*it, tmpNode) == true)
					{
						gridsquare->Move(glm::vec3(0.0f, 5.0f, 0.0f)); // to check the bastard is working
						tmpNode.isBlocked = true;
					}
					else {
						tmpNode.isBlocked = false;
					}
				}
			}
			//add game object to the render loop
			cout << " ( " << gridsquare->getPosition().x << " , " << gridsquare->getPosition().y << " , " << gridsquare->getPosition().z << " ) " << endl;
			gameObjects.push_back(gridsquare);

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
	std::vector<std::vector<Node>>::iterator it;
	for (it = rowVector.begin(); it != rowVector.end(); it++)
	{
		//iterate through each colum of each row
		std::vector<Node>::iterator it1;
		for (it1 = (*it).begin(); it1 != (*it).end(); it1++)
		{
			std::vector<GameObject*>::iterator it2;
			for (it2 = gameObjects.begin(); it2 != gameObjects.end(); it2++)
			{
				//cycle through all the game objects
				if ((*it2)->getCollider())
				{
					//check
					if (checkaltGridCollision(*it2, *it1) == true)
					{
						cout << "getting here" << endl;
						if ((*it1).isBlocked == false)
						{
							GameObject* gridsquare;
							gridsquare = new Player(cube);
							gridsquare->setShader(shader);
							gridsquare->Scale(glm::vec3(10.0, 10.0, 1.0));
							//gridsquare->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
							gridsquare->Move(glm::vec3((*it1).position.x, -17.5f, (*it1).position.z));
							gridsquare->setAnim(0);
							gameObjects.push_back(gridsquare);
							(*it1).isBlocked = true;
							
						}
					}
				}
			}
		}

	}
}

bool Grid::checkaltGridCollision(GameObject* a, Node b)
{

	if (abs(a->getCollider()->getPos().x - b.position.x) > (a->getCollider()->getHW() + (nodeDiameter/2))) return false;
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
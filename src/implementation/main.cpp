#include "config.h"
#include "tools.h"
#include "treeNode.h"

float randomAngle(float fAngle, float fAngleOffset, float angleOffsetFluctuations, int iSide)
{
	return fAngle + (zer::athm::toRadians(fAngleOffset + zer::athm::rand_int(-angleOffsetFluctuations, angleOffsetFluctuations)) * iSide);
}

int randomLength(int iLength, int iLengthFluctuations)
{
	return zer::athm::rand_int(10) > 4 ? iLength - iLengthFluctuations : iLength;
}

void tree(sf::RenderWindow& window, std::map<std::string, float>& cfg)
{
	int iRepetitions = cfg["repetitions"];
	int iSide = 1;

	float fAngle = zer::athm::toRadians(270);
	float fY = mWH;
	float fX = mWW * 0.5;
	float fBranchLength = cfg["branchLength"];
	float fBranchWith = cfg["branchWidth"];

	std::vector<TreeNode> nodes;

	while (true)
	{
		if (!iRepetitions)
		{
			/*
				Set leaf.
			*/
			if (cfg["includeLeaves"])
				drawPattern(window, fAngle, fY, fX, cfg["leafLength"], cfg["leafWidth"], sf::Color(0, zer::athm::rand_int(80, 240), 0));

			nodes.erase(nodes.end() - 1);

			/*
				Moving back to first not closed node.
			*/
			for (int i = nodes.size() - 1; i >= 0; --i)
			{
				++iRepetitions;

				if (nodes[i].iSide > 0)
				{
					nodes[i].iSide = -nodes[i].iSide;
					fAngle = randomAngle(nodes[i].fAngle, cfg["angleOffset"], cfg["angleOffsetFluctuations"], nodes[i].iSide);
					fY = nodes[i].fY;
					fX = nodes[i].fX;
					fBranchLength = randomLength(nodes[i].fBranchLength - 1, cfg["branchLengthFluctuations"]);
					fBranchWith = nodes[i].fBranchWith * cfg["branchWidthReductionFactor"];
					break;
				}
				else
				{
					nodes.erase(nodes.begin() + i);
				}
			}

			if (!nodes.size())
				break;
		}

		/*
			Set branch.
		*/
		drawPattern(window, fAngle, fY, fX, fBranchLength, fBranchWith, sf::Color(102, 53, 27));

		nodes.push_back(TreeNode(fAngle, fY, fX, fBranchLength, fBranchWith));

		fAngle = randomAngle(fAngle, cfg["angleOffset"], cfg["angleOffsetFluctuations"], iSide);
		fBranchLength = randomLength(fBranchLength - 1, cfg["branchLengthFluctuations"]);
		fBranchWith = fBranchWith * cfg["branchWidthReductionFactor"];

		--iRepetitions;
	}
}

int loop(sf::RenderWindow& window, std::map<std::string, float>& cfg)
{
	displayConsoleInformation(cfg);

	window.clear(sf::Color(109, 216, 252));

	tree(window, cfg);

	window.display();

	while (window.isOpen())
	{
		switch (eventListener(window))
		{
			case (CLOSE_EVENT_CODE):
				window.close();
				break;

			case RESTART_EVENT_CODE:
				init(window);
				break;
		}
	}

	return 0;
}

int init(sf::RenderWindow& window)
{
	std::map<std::string, float> cfg = readConfig(mConfigPath);

	return loop(window, cfg);
}
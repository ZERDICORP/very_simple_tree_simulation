class TreeNode
{
	public:
		inline TreeNode() {}
		inline TreeNode(float fAngle, float fY, float fX, float fBranchLength, float fBranchWith)
		{
			this -> fAngle = fAngle;
			this -> fY = fY;
			this -> fX = fX;
			this -> fBranchLength = fBranchLength;
			this -> fBranchWith = fBranchWith;
		}
		
		float fAngle;
		float fY;
		float fX;
		float fBranchLength;
		float fBranchWith;

		int iSide = 1;
};
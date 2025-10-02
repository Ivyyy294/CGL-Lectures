using GameFramework;
namespace AI_Strategy
{
    /*
     * This class derives from Soldier and provides a new move method. Your assignment should
     * do the same - but with your own movement strategy.
     */
    public class DummySoldier : Soldier
    {
        bool advance = false;
        bool deployed = false;
        /*
         * This move method is a mere copy of the base movement method.
         */
        public override void Move()
        {
            if (deployed)
            {
                int x = posX;
                int y = posY;

                for (int i = speed; i > 0; i--)
                {
                    if (MoveTo(x, y + i)) return;
                    if (MoveTo(x + i, y + i)) return;
                    if (MoveTo(x - i, y + i)) return;
                    if (MoveTo(x + i, y)) return;
                    if (MoveTo(x - i, y)) return;
                    if (MoveTo(x, y - i)) return;
                    if (MoveTo(x - i, y - i)) return;
                    if (MoveTo(x + i, y - i)) return;
                }
            }
            else if (IsRegimentComplete())
                deployed = true;
            else if (posY < DummyStrategy.regimentDepth -1)
                MoveTo (posX, posY + 1);
        }
        private bool IsRegimentComplete()
        {
            for (int i = 0; i < DummyStrategy.regimentDepth; ++i)
            {
                if (!IsRowComplete(i))
                    return false;
            }

            return true;
        }

        private bool IsRowComplete (int row)
        {
            for (int i = 0; i < DummyStrategy.regimentWidth; ++i)
            {
                if (player.EnemyLane.GetCellAt(DummyStrategy.regimentStartIndex + i, row).Unit == null)
                    return false;
            }
            return true;
        }
    }
}

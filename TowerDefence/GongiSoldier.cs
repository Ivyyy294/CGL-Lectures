using GameFramework;
using System.Collections.Generic;
namespace AI_Strategy
{
    /*
     * This class derives from Soldier and provides a new move method. Your assignment should
     * do the same - but with your own movement strategy.
     */
    public class GongiSoldier : Soldier
    {
        /*
         * This move method is a mere copy of the base movement method.
         */
        public override void Move()
        {
            if (speed > 0 && posY < PlayerLane.HEIGHT)
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
        }

        protected override List<Unit> SortTargetsInRange(List<Unit> targets)
        {
            // Sort by highest health first weaken the target
            targets.Sort((a, b) => b.Health.CompareTo(a.Health));
            return targets;
        }


    }
}

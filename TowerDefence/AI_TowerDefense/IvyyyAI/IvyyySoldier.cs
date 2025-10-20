using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AI_Strategy
{
    /*
     * This class derives from Soldier and provides a new move method. Your assignment should
     * do the same - but with your own movement strategy.
     */
    public class Regiment
    {
        public List <IvyyySoldier> soldiers = new();
    }

    public class IvyyySoldier : Soldier
    {
        struct Waypoint
        {
            public int x;
            public int y;
        }

        bool m_deployed = false;
        ActiveRegimentSettings m_activeRegimentSettings;

        public void SetRegimentSettings(ActiveRegimentSettings activeRegimentSettings)
        {
            m_activeRegimentSettings = activeRegimentSettings;
        }

        public void Deploy()
        {
            m_deployed = true;
        }
        /*
         * This move method is a mere copy of the base movement method.
         */
        public override void Move()
        {
            Waypoint waypoint = new();

            if (!IsTowerInRange(ref waypoint))
            {
                if (!m_deployed)
                {
                    waypoint.x = posX;
                    waypoint.y = posY + (posY < m_activeRegimentSettings.Depth - 1 ? 1 : 0);
                }
                else
                {
                    waypoint.x = posX;
                    waypoint.y = posY+1;
                }
            }
            
            ApproachWaypoint (ref waypoint);
        }

        private bool IsTowerInRange(ref Waypoint waypoint)
        {
            List<Tower> towers = new List<Tower>();

            for (int x = Math.Max(0, PosX-2); x < Math.Min(7, PosX+3); ++x)
            {
                for (int y = Math.Max(0, PosY); y < Math.Min(20, PosY + 3); ++y)
                {
                    Unit unit = player.EnemyLane.GetCellAt(x, y).Unit;

                    if (unit is Tower)
                        towers.Add ((Tower)unit);
                }
            }

            towers = towers.OrderBy(x=>x.Health).ToList();

            if (towers.Count > 0)
            {
                Tower tower = towers[0];
                waypoint.x = tower.PosX;
                waypoint.y = tower.PosY;
                return true;
            }

            return false;
        }

        private void ApproachWaypoint (ref Waypoint waypoint)
        {
            int xOffset = posX - waypoint.x;
            int yOffset = posY - waypoint.y;

            int xDiff = Math.Abs (xOffset);
            int yDiff = Math.Abs (yOffset);

            int x = posX - Math.Sign (xOffset);
            int y = posY - Math.Sign(yOffset);

            for (int i = speed; i > 0; i--)
            {
                if (xDiff >= yDiff)
                    TryMoveX (x, y);
                else
                    TryMoveY (x, y);
            }
        }

        private void TryMoveX (int x, int y)
        {
            //Try linear x
            if (MoveTo(x, posY)) return;
            //Try Diagona x
            if (MoveTo(x, y)) return;
            //try linear y
            if (MoveTo(posX, y)) return;
        }

        private void TryMoveY(int x, int y)
        {
            //Try linear Y
            if (MoveTo(PosX, y)) return;
            //Try Diagona y
            if (MoveTo(x, y)) return;
            //try linear x
            if (MoveTo(x, PosY)) return;
        }
    }
}

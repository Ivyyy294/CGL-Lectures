using Agent_System;
using GameFramework;

namespace AI_Strategy
{
    public class TowerDefensePerimeter
    {
        int m_startX;
        int m_startY;
        int m_colums;
        int m_rows;

        public int SoldierCount { get; private set;}

        public TowerDefensePerimeter (int x, int y, int c, int r)
        {
            m_startX = x;
            m_startY = y;
            m_colums = c;
            m_rows = r;
        }

        public void Update (TowerDefensePerception perception)
        {
            SoldierCount = GetEnemyCount (m_startX, m_startY, m_rows, m_colums, perception);
        }

        private int GetEnemyCount(int startX, int startY, int rCount, int cCount, TowerDefensePerception perception)
        {
            int count = 0;

            for (int r = 0; r < rCount; ++r)
            {
                for (int c = 0; c < cCount; ++c)
                {
                    Cell cell = perception.Player.HomeLane.GetCellAt(startX + c, startY + r);

                    if (cell.Unit != null)
                        count++;
                }
            }

            return count;
        }
    }

    public class TowerDefenseAgentState : AgentState<TowerDefensePerception>
    {
        public int Gold { get; private set; }
        public int TowerCount { get; private set; }
        public int EnemyCount { get; private set; }
        public int RegimentCounter { get; set;}
        public Player Player { get; private set; }

        public TowerDefensePerimeter[] EnemySpawn { get; private set; }

        public int DefenseRerimeter { get; private set; }

        public TowerDefensePerception.ActionTyp ActionTyp {get; private set;}

        //Enemy Spawn
        public TowerDefenseAgentState()
        {
            EnemySpawn = new TowerDefensePerimeter[3];
            EnemySpawn[0] = new TowerDefensePerimeter(0, 0, 3, 3);
            EnemySpawn[1] = new TowerDefensePerimeter(2, 0, 3, 3);
            EnemySpawn[2] = new TowerDefensePerimeter(4, 0, 3, 3);
        }

        public override void Update(TowerDefensePerception perception)
        {
            Gold = perception.Player.Gold;
            TowerCount = perception.Player.HomeLane.TowerCount();
            EnemyCount = perception.Player.HomeLane.SoldierCount();
            ActionTyp = perception.CurrentActionTyp;
            Player = perception.Player;

            for (int i = 0; i < EnemySpawn.Length; ++i)
                EnemySpawn[i].Update(perception);

            if (EnemySpawn[0].SoldierCount > EnemySpawn[1].SoldierCount
                && EnemySpawn[0].SoldierCount > EnemySpawn[2].SoldierCount)
                DefenseRerimeter = 0;
            else if (EnemySpawn[2].SoldierCount > EnemySpawn[1].SoldierCount
                && EnemySpawn[2].SoldierCount > EnemySpawn[0].SoldierCount)
                DefenseRerimeter = 2;
            else
                DefenseRerimeter = 1;
        }
    }
}

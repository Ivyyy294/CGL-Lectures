using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace AI_Strategy
{
    public class DummyStrategy : StrategyStateMachine
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        public DummyStrategy(Player player) : base(player)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.AddInstance (player.Name);
            m_activeRegimentSettings.Width = 2;
            m_activeRegimentSettings.Depth = 3;
            m_activeRegimentSettings.StartIndex = 0;
            m_activeRegimentSettings.SoldierLane = player.EnemyLane;

            Push (new DummyBrain(this));
        }
        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList;
        }
    }

    public class DummyBrain : StrategyState
    {
        ActiveRegimentSettings m_activeRegimentSettings;
        int regimentCounter = 0;
        public DummyBrain(StrategyStateMachine stateMachine) : base(stateMachine)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.GetInstance (m_player.Name);
        }
        public override void Continue()
        {
            if (regimentCounter >= 1 && m_player.HomeLane.SoldierCount() < 20)
            {
                regimentCounter = 0;
                m_stateMachine.Push(new DummyTowerDeploy(m_stateMachine));
            }
            else
            {
                regimentCounter++;
                m_stateMachine.Push(new DeployRegimentState(m_stateMachine));
            }
        }

        public override void DeploySoldiers()
        {
        }

        public override void DeployTowers()
        {
        }

        public override void Enter()
        {
            m_stateMachine.Push(new DeployRegimentState(m_stateMachine));
        }

        public override void Exit()
        {
        }
    }

    public class DummyTowerDeploy : StrategyState
    {
        bool baseLineDone = false;
        int secondaryDefenseGrid = -1;
        public DummyTowerDeploy(StrategyStateMachine stateMachine) : base(stateMachine)
        {
        }

        public override void Continue()
        {
        }

        public override void DeploySoldiers()
        {
        }

        public override void DeployTowers()
        {
            if (!baseLineDone)
            {
                if (m_player.TryBuyTower<Tower>(2, 4) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
                if (m_player.TryBuyTower<Tower>(3, 5) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
                if (m_player.TryBuyTower<Tower>(4, 4) == Player.TowerPlacementResult.NotEnoughGold)
                    return;

                baseLineDone = true;
                return;
            }

            if (secondaryDefenseGrid == -1)
                secondaryDefenseGrid = GetSecondaryDefenseGrid();

            if (secondaryDefenseGrid == 0)
            {
                if (m_player.TryBuyTower<Tower>(0, 4) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
                if (m_player.TryBuyTower<Tower>(1, 5) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
            }
            else if (secondaryDefenseGrid == 1)
            {
                if (m_player.TryBuyTower<Tower>(1, 5) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
                if (m_player.TryBuyTower<Tower>(5, 5) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
            }
            else 
            {
                if (m_player.TryBuyTower<Tower>(5, 5) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
                if (m_player.TryBuyTower<Tower>(6, 4) == Player.TowerPlacementResult.NotEnoughGold)
                    return;
            }

            m_stateMachine.Pop();
        }

        public override void Enter()
        {
        }

        public override void Exit()
        {
        }

        private int GetSecondaryDefenseGrid()
        {
            int cLeft = GetEnemyCount(0);
            int cCenter = GetEnemyCount(2);
            int cRight = GetEnemyCount(4);

            if (cLeft > cCenter && cLeft > cRight)
                return 0;
            else if (cRight > cLeft && cRight > cCenter)
                return 2;
            else
                return 1;
        }
        private int GetEnemyCount (int startIndex)
        {
            int count = 0;

            for (int r = 0; r < 2; ++r)
            {
                for (int c = 0; c < 3; ++c)
                {
                    Cell cell = m_player.HomeLane.GetCellAt (r, startIndex + c);

                    if (cell.Unit != null)
                        count++;
                }
            }

            return count;
        }
    }
}

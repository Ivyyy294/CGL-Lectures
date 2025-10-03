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
            m_activeRegimentSettings.Width = 3;
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
            if (regimentCounter >= 1)
            {
                regimentCounter = 0;
                m_stateMachine.Push(new DummyTowerDeploy(m_stateMachine));
            }
            else
            {
                regimentCounter++;
                EvaluateRegimentSize();
                SetRegimentStartIndex();
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
            m_stateMachine.Push(new DummyTowerDeploy(m_stateMachine));
        }

        public override void Exit()
        {
        }

        private void EvaluateRegimentSize()
        {
            if (m_player.Gold >= 42)
                m_activeRegimentSettings.Width = 6;
            else if (m_player.Gold >= 36)
                m_activeRegimentSettings.Width = 6;
            else if (m_player.Gold >= 30)
                m_activeRegimentSettings.Width = 5;
            else if (m_player.Gold >= 24)
                m_activeRegimentSettings.Width = 4;
            else
                m_activeRegimentSettings.Width = 3;
        }

        private void SetRegimentStartIndex()
        {
            Random r = new Random();
            m_activeRegimentSettings.StartIndex = r.Next(0, 7 - m_activeRegimentSettings.Width);
        }
    }

    public class DummyTowerDeploy : StrategyState
    {
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
            if (m_player.TryBuyTower<Tower>(1, 4) == Player.TowerPlacementResult.NotEnoughGold)
                return;
            if (m_player.TryBuyTower<Tower>(3, 4) == Player.TowerPlacementResult.NotEnoughGold)
                return;
            if (m_player.TryBuyTower<Tower>(5, 4) == Player.TowerPlacementResult.NotEnoughGold)
                return;
            if (m_player.TryBuyTower<Tower>(2, 5) == Player.TowerPlacementResult.NotEnoughGold)
                return;
            if (m_player.TryBuyTower<Tower>(4, 5) == Player.TowerPlacementResult.NotEnoughGold)
                return;

            m_stateMachine.Pop();
        }

        public override void Enter()
        {
        }

        public override void Exit()
        {
        }
    }
}

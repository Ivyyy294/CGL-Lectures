using System;
using tower_defence.AI_TowerDefense.IvyyyAI;

namespace AI_Strategy
{
    public class IvyyyUpdateRegimentRule : IvyyyRule
    {
        public IvyyyUpdateRegimentRule (TowerDefenseAgentState state) : base (state)
        {
            m_axis.Add(new IvyyyRuleAxis("ActiveRegimentSettings", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));
            m_axis.Add(new IvyyyRuleAxis("DeployTowers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));
            m_weight = 10f;
        }

        public override void Action(object target)
        {
            m_worldState.ActiveRegimentSettings = new ActiveRegimentSettings();
            m_worldState.ActiveRegimentSettings.Width = 2;
            m_worldState.ActiveRegimentSettings.Depth = 3;
            m_worldState.ActiveRegimentSettings.StartIndex = 0;
            m_worldState.ActiveRegimentSettings.SoldierLane = m_worldState.Player.EnemyLane;

            EvaluateRegimentSize();
            SetRegimentStartIndex();
        }

        private void EvaluateRegimentSize()
        {
            if (m_worldState.Gold >= 42)
                m_worldState.ActiveRegimentSettings.Width = 7;
            else if (m_worldState.Gold >= 36)
                m_worldState.ActiveRegimentSettings.Width = 6;
            else if (m_worldState.Gold >= 30)
                m_worldState.ActiveRegimentSettings.Width = 5;
            else if (m_worldState.Gold >= 24)
                m_worldState.ActiveRegimentSettings.Width = 4;
            else
                m_worldState.ActiveRegimentSettings.Width = 3;
        }

        private void SetRegimentStartIndex()
        {
            Random r = new Random();
            m_worldState.ActiveRegimentSettings.StartIndex = r.Next(0, 7 - m_worldState.ActiveRegimentSettings.Width);
        }
    }
}

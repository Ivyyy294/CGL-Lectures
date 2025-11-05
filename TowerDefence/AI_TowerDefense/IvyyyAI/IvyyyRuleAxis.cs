namespace IvyyyAI
{
    public class IvyyyRuleAxis
    {
        public string Parameter { get; private set; }
        public IvyyyResponseCurve ResponseCurve { get; private set; }

        public IvyyyRuleAxis (string parameter, IvyyyResponseCurve responseCurve)
        {
            Parameter = parameter;
            ResponseCurve = responseCurve;
        }
    }
}

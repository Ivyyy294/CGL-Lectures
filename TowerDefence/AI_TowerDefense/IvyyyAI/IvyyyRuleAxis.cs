namespace IvyyyAI
{
    public class IvyyyRuleAxis
    {
        //Name of input parameter
        public string Parameter { get; private set; }

        //ResponseCurve parameters
        public IvyyyResponseCurve ResponseCurve { get; private set; }

        public IvyyyRuleAxis (string parameter, IvyyyResponseCurve responseCurve)
        {
            Parameter = parameter;
            ResponseCurve = responseCurve;
        }
    }
}

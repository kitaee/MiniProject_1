using System.Runtime.InteropServices;

namespace TCC_GUI;

public partial class App : System.Windows.Application
{
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool AllocConsole();

    protected override void OnStartup(System.Windows.StartupEventArgs e)
    {
#if DEBUG
        AllocConsole();
        Console.WriteLine("[TCC_GUI] Debug console attached.");
#endif
        base.OnStartup(e);
    }
}

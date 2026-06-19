using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Interop;
using nframework.nom;
using NOMHandlerLib.Concrete;
using NOMHandlerLib.Core;

namespace TCC_GUI;

public partial class MainWindow : Window
{
    private readonly NOMHandler nomHandler;
    private bool nfConnectStarted;

    public MainWindow()
    {
        var nomFilePaths = new List<string>
        {
            Environment.CurrentDirectory + @"\UIManager\UIManager.xml"
        };

        nomHandler = new NOMHandler(nomFilePaths);
        nomHandler.MessageSent += OnNOMMessageSent;

        Loaded += MainWindow_Loaded;
        Closed += MainWindow_Closed;
        InitializeComponent();
    }

    private void MainWindow_Loaded(object sender, RoutedEventArgs e)
    {
        (PresentationSource.FromVisual(this) as HwndSource)?.AddHook(nomHandler.WndProcCallback);

        if (!nomHandler.CreateNFConnect())
        {
            SetStatus("Failed: nFConnect create. Check nFConnect.ini and DLLs.");
            MessageBox.Show(
                "Failed to create nFConnect.\nCheck nFConnect.ini and nFramework DLLs in tcc\\bin.",
                "TCC",
                MessageBoxButton.OK,
                MessageBoxImage.Error);
            return;
        }

        nomHandler.DoPlugIn();
        nomHandler.SetWindowHandle(new WindowInteropHelper(this).Handle);
        nomHandler.ExecStart();
        nfConnectStarted = true;
        SetStatus("Ready — click Deploy to send DeployScenarioRequest (id=1001).");
        Log("nFConnect started (UIManager + UDP).");
    }

    private void MainWindow_Closed(object? sender, EventArgs e)
    {
        if (!nfConnectStarted)
            return;

        nomHandler.ExecStop();
        nomHandler.DoPlugOut();
        nomHandler.DestroyNFConnect();
    }

    private void DeployScenarioButton_Click(object sender, RoutedEventArgs e)
    {
        if (!nfConnectStarted)
        {
            SetStatus("nFConnect is not started.");
            MessageBox.Show("nFConnect is not started.", "TCC", MessageBoxButton.OK, MessageBoxImage.Warning);
            return;
        }

        var nomInstance = nomHandler.GetNMessage("DeployScenarioRequest")?.createNOMInstance();
        if (nomInstance == null)
        {
            SetStatus("DeployScenarioRequest not found in UIManager.xml.");
            MessageBox.Show("DeployScenarioRequest is not defined in UIManager.xml.", "TCC");
            return;
        }

        try
        {
            nomInstance.setValue("MessageHeader.MessageID", new NUInteger(1001u));
            nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(44u));
            nomInstance.setValue("Airthreat.AirthreatID", new NUInteger(1u));
            nomInstance.setValue("Airthreat.StartLatitude", new NFloat(37.5f));
            nomInstance.setValue("Airthreat.StartLongitude", new NFloat(127.0f));
            nomInstance.setValue("Airthreat.EndLatitude", new NFloat(37.6f));
            nomInstance.setValue("Airthreat.EndLongitude", new NFloat(127.1f));
            nomInstance.setValue("RadarPositionLatitude", new NFloat(37.55f));
            nomInstance.setValue("RadarPositionLongitude", new NFloat(127.05f));
            nomInstance.setValue("LauncherPositionLatitude", new NFloat(37.52f));
            nomInstance.setValue("LauncherPositionLongitude", new NFloat(127.02f));

            nomHandler.SendNOMMessage(nomInstance);
            SetStatus("Sent DeployScenarioRequest (id=1001) via UDP multicast.");
            Log("DeployScenarioRequest sent (MessageID=1001).");
        }
        catch (Exception ex)
        {
            SetStatus("Send failed — see log.");
            Log("DeployScenarioRequest error: " + ex);
            MessageBox.Show(ex.ToString(), "DeployScenarioRequest", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }

    private void OnNOMMessageSent(NOM nomInstance, EMessageOperation operation)
    {
        if (operation != EMessageOperation.Send)
            return;

        var msg = $"[TCC_GUI] MessageSent: {nomInstance.name}";
        Log(msg);
    }

    private void SetStatus(string text)
    {
        StatusText.Text = text;
    }

    private static void Log(string message)
    {
        var line = $"[{DateTime.Now:HH:mm:ss}] {message}";
        Console.WriteLine(line);
        try
        {
            var path = Path.Combine(Environment.CurrentDirectory, "tcc_deploy.log");
            File.AppendAllText(path, line + Environment.NewLine);
        }
        catch
        {
            // ignore log file errors
        }
    }
}

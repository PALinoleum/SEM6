using OpenPop.Mime;
using OpenPop.Pop3;
using ystem;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp28
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            AuthForm.Visibility = Visibility.Visible;
        }

        List<Message> messages = new List<Message>();
        MailClient mailClient = null;
        private void button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                mailClient = new MailClient(emailbox.Text, passbox.Text);
                messages = mailClient.GetMessages(30);
                foreach(var item in messages) mailListBox.Items.Add(new ListBoxItem(){ Content = string.Format("От : {0}, {1}...", item.Headers.From.DisplayName, item.Headers.Subject), FontSize = 12, });
                AuthForm.Visibility = Visibility.Collapsed;
            }
            catch (Exception) {}
        }

        private void BtnIcon_Click(object sender, RoutedEventArgs e) { MsgForm.Visibility = Visibility.Collapsed; }

        private void mailListBox_PreviewMouseUp(object sender, MouseButtonEventArgs e)
        {
            MsgForm.Visibility = Visibility.Visible;
            msgbody.Text = "";

            if ((sender as ListBox).SelectedIndex < 0) return;
            fromlbl.Content = (messages[(sender as ListBox).SelectedIndex].Headers.From.ToString().Length < 30) ? messages[(sender as ListBox).SelectedIndex].Headers.From.ToString() : String.Concat(messages[(sender as ListBox).SelectedIndex].Headers.From.ToString().Substring(0, 30) + " ...");
            datelbl.Content = (messages[(sender as ListBox).SelectedIndex].Headers.DateSent.ToString().Length < 30) ? messages[(sender as ListBox).SelectedIndex].Headers.DateSent.ToString() : String.Concat(messages[(sender as ListBox).SelectedIndex].Headers.DateSent.ToString().Substring(0, 30) + " ...");
            subjlbl.Content = (messages[(sender as ListBox).SelectedIndex].Headers.Subject.ToString().Length < 30) ? messages[(sender as ListBox).SelectedIndex].Headers.Subject.ToString() : String.Concat(messages[(sender as ListBox).SelectedIndex].Headers.Subject.ToString().Substring(0, 30) + " ...");

            foreach(var item in messages[(sender as ListBox).SelectedIndex].MessagePart.MessageParts) msgbody.Text += item.IsText ? System.Text.Encoding.UTF8.GetString(item.Body) : "";
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            mailClient.SendMessage(to_email.Text, send_subject.Text, msg_body.Text);
            to_email.Text = send_subject.Text = msg_body.Text = "";
        }
    }
}

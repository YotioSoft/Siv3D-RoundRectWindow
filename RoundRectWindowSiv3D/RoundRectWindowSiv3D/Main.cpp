#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include <Siv3D/Windows.hpp>

namespace
{
    LONG_PTR g_baseProc = 0;
    LRESULT CALLBACK CustomWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // 自前のイベント処理をする

        // もともとOpenSiv3Dで呼ばれてたWindowProcを呼ぶ
        return CallWindowProc(reinterpret_cast<WNDPROC>(g_baseProc), hWnd, message, wParam, lParam);
    }
}

void Main()
{
    Window::SetStyle(WindowStyle::Frameless);
    Scene::SetBackground(Color(Palette::White));

    // Windowハンドル取得
    auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

    // 自前のWindowProcに切り替え
    // 返り値は元々のWindowProc
    g_baseProc = ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(::CustomWindowProc));

    auto hRegion = CreateRoundRectRgn(0, 0, 640, 480, 100, 100);
    SetWindowRgn(hWnd, hRegion, 1);

    // マウスクリックした地点の記録用
    Point mouse_clicked;

    while (System::Update()) {
        // ウィンドウの移動
        if (MouseL.down()) {
            mouse_clicked = Cursor::Pos();
        }
        if (MouseL.pressed()) {
            Window::SetPos(Cursor::ScreenPos() - mouse_clicked);
        }

        Print << U"Hello World";
    }
}

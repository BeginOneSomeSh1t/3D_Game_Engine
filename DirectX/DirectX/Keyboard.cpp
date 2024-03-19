#include "Keyboard.h"

bool Keyboard::KeyIsPressed(UCHAR keycode) const noexcept
{
    return keystates[keycode];
}

std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept
{
    if (keybuffer.size() > 0u)
    {
        Keyboard::Event e = keybuffer.front();
        keybuffer.pop();
        return e;
    }
    else
        return {};
}

bool Keyboard::KeyIsEmpty() const noexcept
{
    return keybuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
    keybuffer = std::queue<Event>();
}

char Keyboard::ReadChar() noexcept
{
    if (charbuffer.size() > 0u)
    {
        UCHAR charcode = charbuffer.front();
        charbuffer.pop();
        return charcode;
    }
    else
        return 0;
}

bool Keyboard::CharIsEmpty() const noexcept
{
    return charbuffer.empty();
}

void Keyboard::FlushChar() noexcept
{
    charbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
    FlushKey();
    FlushChar();
}

void Keyboard::EnableAutorepeat() noexcept
{
    autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
    autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept
{
    return autorepeatEnabled;
}

void Keyboard::BindToOnKeyPressed(KeyboardKeySignature::FuncPtr sub) noexcept
{
    OnKeyPressed_DELEGATED += sub;
}

void Keyboard::BindToOnKeyReleased(KeyboardKeySignature::FuncPtr sub) noexcept
{
    OnKeyReleased_DELEGATED += sub;
}

void Keyboard::OnKeyPressed(UCHAR keycode) noexcept
{

    keystates[keycode] = true;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
    OnKeyPressed_DELEGATED(std::move(keycode));
    TrimBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(UCHAR keycode) noexcept
{
    keystates[keycode] = false;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
    OnKeyReleased_DELEGATED(std::move(keycode));
    TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
    charbuffer.push(character);
    TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept
{
    keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
    while (buffer.size() > bufferSize)
        buffer.pop();
}

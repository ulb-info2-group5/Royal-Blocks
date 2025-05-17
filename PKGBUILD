pkgname=royal-blocks
pkgver=1.0.0
pkgrel=1
options=(!debug strip)
pkgdesc="A homemade Royal Tetris in C++"
arch=('x86_64')
url="https://github.com/ulb-info2-group5/Tetris-Blocks"
license=('GPL3')
depends=('qt5-base' 'boost')
makedepends=('gcc' 'make' 'cmake' 'boost' 'qt5-base')
source=("https://github.com/ulb-info2-group5/Tetris-Blocks/releases/download/v1.0.0/royal-blocks-1.0.0-1-x86_64.pkg.tar.zst")
sha256sums=('852110c506f48e9c7c59d2cd866bb319901a072dd5e952374c727500e0d269e9')

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make
}

package() {
  install -Dm755 "$srcdir/$pkgname-$pkgver/royal-blocks-gui" "$pkgdir/usr/bin/royal-blocks"
  install -Dm755 "$srcdir/$pkgname-$pkgver/royal-blocks-tui" "$pkgdir/usr/bin/royal-blocks-tui"
  install -Dm644 "$srcdir/$pkgname-$pkgver/royal-blocks-server" "$pkgdir/usr/bin/royal-blocks-server"

  install -Dm644 "$srcdir/$pkgname-$pkgver/royal-blocks.desktop" "$pkgdir/usr/share/applications/royal-blocks.desktop"
  install -Dm644 "$srcdir/$pkgname-$pkgver/royal-blocks-tui.desktop" "$pkgdir/usr/share/applications/royal-blocks-tui.desktop"
  install -Dm644 "$srcdir/$pkgname-$pkgver/royal-blocks-server.desktop" "$pkgdir/usr/share/applications/royal-blocks-server.desktop"

  install -Dm644 "$srcdir/$pkgname-$pkgver/logo_1024x1024.png" "$pkgdir/usr/share/icons/hicolor/1024x1024/apps/royal-blocks.png"
}
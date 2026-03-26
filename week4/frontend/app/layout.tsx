export const metadata = {
  title: "ONBOARD-WEEK4",
  description: "CSP/CCSDS Packet Handler",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="ko">
      <body>{children}</body>
    </html>
  );
}

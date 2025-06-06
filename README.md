# Shopping System

A C++ console-based shopping system that simulates an e-commerce platform with credit card processing capabilities.

## Features

- User Management
  - Add new users with credit card information
  - Store user details including card numbers, names, expiration dates, CVV, and credit limits
  - Support for multiple users (configurable limit)

- Shopping Categories
  1. Fruits
  2. Clothing
  3. Medicine
  4. Technology
  5. Dairy
  6. Books

- Shopping Features
  - Browse items by category
  - View item prices
  - Check item availability
  - Process payments
  - Track purchase history
  - Manage inventory

## How to Use

1. **Compile the Program**
   ```bash
   g++ "pf project.cpp" -o "pf project"
   ```

2. **Run the Program**
   ```bash
   .\pf project.exe
   ```

3. **Main Menu Options**
   - Option 1: Add User
     - Enter card number
     - Enter cardholder name
     - Enter expiration date
     - Enter CVV
     - Set credit limit

   - Option 2: Make a Purchase
     - Select category (1-6)
     - Choose item from category
     - Enter user ID
     - Verify credit card details
     - Complete purchase

   - Option 3: View Purchase History
     - Enter user ID to view past purchases

   - Option 4: Exit Program

## System Requirements

- C++ compiler (supporting C++11 or later)
- Windows operating system (for the executable)
- Console/terminal access

## Technical Details

- Maximum Users: 1 (configurable via `MAX_USERS` constant)
- Categories: 6
- Items per Category: 2
- Inventory tracking for each item
- Credit card balance management
- Purchase history tracking

## Security Features

- Credit card verification
- Balance checking
- CVV validation
- Expiration date verification

## Notes

- The system maintains a stock of 10 items for each product
- Credit limits are enforced for purchases
- Purchase history is maintained per user
- The system supports real-time inventory updates

## Limitations

- Maximum number of users is limited (currently set to 1)
- Basic console interface
- No persistent data storage (data is lost when program exits)
- Limited number of items per category

## Future Improvements

- Add data persistence
- Implement user authentication
- Add more product categories
- Enhance security features
- Add admin interface
- Implement refund system
- Add search functionality 
import React from 'react';
import PropTypes from 'prop-types';
import styles from './AuthForm.css';
import Card, {CardContent} from 'material-ui/Card';
import Button from 'material-ui/Button';
import Typography from 'material-ui/Typography';
import {SocialIcon} from 'react-social-icons';

export const AuthForm = ({ onLogin }) => (
	<div>
		<Card className={styles.card}>
			<Button className={styles.loginButton} onClick={onLogin.bind(null, 'github')}>
				<div className={styles.socialIcon}>
					<SocialIcon network="github" color="#333"/>
				</div>
				<Typography className={styles.title}>
					Войти через Github
				</Typography>
			</Button>
		</Card>
	</div>
);

AuthForm.propTypes = {
	onLogin: PropTypes.func.isRequired,
};

export default AuthForm;
